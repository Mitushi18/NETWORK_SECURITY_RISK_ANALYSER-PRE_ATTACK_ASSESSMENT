#include "network/PortScanner.h"
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <algorithm>

#pragma comment(lib, "ws2_32.lib")

struct ScanContext {
    PortScanner* scanner;
    std::string ip;
    int endPort;
    volatile LONG nextPort;
    volatile LONG completed;
    int total;
    std::vector<int> openPorts;
    CRITICAL_SECTION resultLock;
    CRITICAL_SECTION outputLock;
};

PortScanner::PortScanner()
{
    WSADATA data{};
    WSAStartup(MAKEWORD(2, 2), &data);
}

PortScanner::~PortScanner()
{
    WSACleanup();
}

bool PortScanner::isPortOpen(const std::string& ipAddress, int port)
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) return false;

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(static_cast<u_short>(port));
    address.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    if (address.sin_addr.s_addr == INADDR_NONE) {
        closesocket(sock);
        return false;
    }

    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    int result = connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address));

    if (result == 0) {
        closesocket(sock);
        return true;
    }

    int error = WSAGetLastError();
    if (error != WSAEWOULDBLOCK && error != WSAEINPROGRESS) {
        closesocket(sock);
        return false;
    }

    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(sock, &writeSet);

    timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    result = select(0, nullptr, &writeSet, nullptr, &timeout);

    int socketError = 1;
    if (result > 0) {
        int length = sizeof(socketError);
        getsockopt(sock, SOL_SOCKET, SO_ERROR,
                   reinterpret_cast<char*>(&socketError), &length);
    }

    closesocket(sock);
    return result > 0 && socketError == 0;
}

DWORD WINAPI scanWorker(LPVOID parameter)
{
    ScanContext* context = static_cast<ScanContext*>(parameter);

    while (true) {
        int port = static_cast<int>(InterlockedIncrement(&context->nextPort));
        if (port > context->endPort) break;

        if (context->scanner->isPortOpen(context->ip, port)) {
            EnterCriticalSection(&context->resultLock);
            context->openPorts.push_back(port);
            LeaveCriticalSection(&context->resultLock);

            EnterCriticalSection(&context->outputLock);
            std::cerr << "OPEN " << port << std::endl;
            LeaveCriticalSection(&context->outputLock);
        }

        int count = static_cast<int>(InterlockedIncrement(&context->completed));

        if (count % 5 == 0 || count == context->total) {
            EnterCriticalSection(&context->outputLock);
            std::cerr << "PROGRESS " << count << " "
                      << context->total << std::endl;
            LeaveCriticalSection(&context->outputLock);
        }
    }

    return 0;
}

std::vector<int> PortScanner::scanPorts(
    const std::string& ipAddress, int startPort, int endPort)
{
    std::vector<int> empty;

    if (startPort < 1) startPort = 1;
    if (endPort > 65535) endPort = 65535;
    if (startPort > endPort) return empty;

    ScanContext context;
    context.scanner = this;
    context.ip = ipAddress;
    context.endPort = endPort;
    context.nextPort = startPort - 1;
    context.completed = 0;
    context.total = endPort - startPort + 1;

    InitializeCriticalSection(&context.resultLock);
    InitializeCriticalSection(&context.outputLock);

    int workerCount = context.total < 32 ? context.total : 32;
    HANDLE threads[32] = {};
    int created = 0;

    for (int i = 0; i < workerCount; ++i) {
        HANDLE thread = CreateThread(
            nullptr, 0, scanWorker, &context, 0, nullptr
        );
        if (thread != nullptr) {
            threads[created++] = thread;
        }
    }

    if (created == 0) {
        scanWorker(&context);
    } else {
        WaitForMultipleObjects(created, threads, TRUE, INFINITE);
        for (int i = 0; i < created; ++i) CloseHandle(threads[i]);
    }

    DeleteCriticalSection(&context.resultLock);
    DeleteCriticalSection(&context.outputLock);

    std::sort(context.openPorts.begin(), context.openPorts.end());
    return context.openPorts;
}
