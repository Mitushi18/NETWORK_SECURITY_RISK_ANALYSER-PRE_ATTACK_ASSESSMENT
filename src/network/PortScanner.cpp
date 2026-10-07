#include "network/PortScanner.h"

#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

PortScanner::PortScanner()
{
    WSADATA wsaData;

    WSAStartup(
        MAKEWORD(2, 2),
        &wsaData
    );
}

PortScanner::~PortScanner()
{
    WSACleanup();
}

bool PortScanner::isPortOpen(
    const std::string& ipAddress,
    int port
)
{
    SOCKET sock = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP
    );

    if (sock == INVALID_SOCKET)
    {
        return false;
    }

    sockaddr_in targetAddress{};

    targetAddress.sin_family = AF_INET;
    targetAddress.sin_port = htons(
        static_cast<u_short>(port)
    );

    targetAddress.sin_addr.s_addr =
        inet_addr(ipAddress.c_str());

    if (targetAddress.sin_addr.s_addr == INADDR_NONE)
    {
        closesocket(sock);
        return false;
    }

    // Make the socket non-blocking.
    u_long nonBlocking = 1;

    ioctlsocket(
        sock,
        FIONBIO,
        &nonBlocking
    );

    // Start connection.
    connect(
        sock,
        reinterpret_cast<sockaddr*>(&targetAddress),
        sizeof(targetAddress)
    );

    // Wait up to 100 milliseconds.
    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(sock, &writeSet);

    timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = 100000;

    int result = select(
        0,
        nullptr,
        &writeSet,
        nullptr,
        &timeout
    );

    bool portOpen = false;

    if (result > 0 && FD_ISSET(sock, &writeSet))
    {
        int error = 0;
        int errorSize = sizeof(error);

        getsockopt(
            sock,
            SOL_SOCKET,
            SO_ERROR,
            reinterpret_cast<char*>(&error),
            &errorSize
        );

        portOpen = (error == 0);
    }

    closesocket(sock);

    return portOpen;
}

std::vector<int> PortScanner::scanPorts(
    const std::string& ipAddress,
    int startPort,
    int endPort
)
{
    std::vector<int> openPorts;

    if (startPort < 1)
    {
        startPort = 1;
    }

    if (endPort > 65535)
    {
        endPort = 65535;
    }

    if (startPort > endPort)
    {
        return openPorts;
    }

    for (int port = startPort;
         port <= endPort;
         ++port)
    {
        if (isPortOpen(ipAddress, port))
        {
            openPorts.push_back(port);
        }
    }

    return openPorts;
}