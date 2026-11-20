#include <winsock2.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "network/PortScanner.h"
#include "network/Port.h"
#include "network/ServiceDetector.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: nsra_scanner.exe <host> <start_port> <end_port>\n";
        return 1;
    }

    std::string target = argv[1];
    int startPort = std::atoi(argv[2]);
    int endPort = std::atoi(argv[3]);

    if (startPort < 1 || endPort > 65535 ||
        startPort > endPort || endPort - startPort > 999)
    {
        std::cerr << "Invalid port range. Maximum range: 1000 ports.\n";
        return 1;
    }

    PortScanner scanner;

    hostent* host = gethostbyname(target.c_str());

    if (host == NULL || host->h_addr_list[0] == NULL)
    {
        std::cerr << "Unable to resolve target: " << target << "\n";
        return 1;
    }

    in_addr address;
    address.s_addr = *reinterpret_cast<unsigned long*>(
        host->h_addr_list[0]
    );

    std::string resolvedIP = inet_ntoa(address);

    std::vector<int> openPorts =
        scanner.scanPorts(resolvedIP, startPort, endPort);

    ServiceDetector detector;

    std::cout << "{\n";
    std::cout << "  \"target\": \"" << target << "\",\n";
    std::cout << "  \"resolved_ip\": \"" << resolvedIP << "\",\n";
    std::cout << "  \"start_port\": " << startPort << ",\n";
    std::cout << "  \"end_port\": " << endPort << ",\n";
    std::cout << "  \"open_ports\": [";

    for (size_t i = 0; i < openPorts.size(); ++i)
    {
        Port port(openPorts[i], "TCP");
        detector.detectService(port);

        if (i > 0)
            std::cout << ",";

        std::cout << "\n    {";
        std::cout << "\"port\": " << port.getPortNumber() << ",";
        std::cout << " \"protocol\": \"TCP\",";
        std::cout << " \"service\": \"" << port.getServiceName() << "\"";
        std::cout << "}";
    }

    if (!openPorts.empty())
        std::cout << "\n  ";

    std::cout << "]\n}\n";

    return 0;
}
