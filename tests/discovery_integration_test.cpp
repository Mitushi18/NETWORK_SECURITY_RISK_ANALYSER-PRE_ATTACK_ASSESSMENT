#include <iostream>
#include <vector>

#include "network/HostDiscovery.h"
#include "network/Port.h"

int main()
{
    HostDiscovery discovery;

    std::string ipAddress = "127.0.0.1";

    std::cout << "Network Discovery Integration Test\n";
    std::cout << "-----------------------------------\n";

    Host host =
        discovery.discoverHostWithPorts(
            ipAddress,
            1,
            1000
        );

    std::cout << "Host: "
              << host.getIpAddress()
              << "\n";

    std::cout << "\nOpen Ports\n";
    std::cout << "----------\n";

    const std::vector<Port>& ports =
        host.getOpenPorts();

    if (ports.empty())
    {
        std::cout << "No open ports found.\n";
    }
    else
    {
        for (const Port& port : ports)
        {
            std::cout
                << port.getPortNumber()
                << "/"
                << port.getProtocol()
                << " -> "
                << port.getServiceName()
                << "\n";
        }
    }

    std::cout << "\nTotal open ports: "
              << ports.size()
              << "\n";

    return 0;
}