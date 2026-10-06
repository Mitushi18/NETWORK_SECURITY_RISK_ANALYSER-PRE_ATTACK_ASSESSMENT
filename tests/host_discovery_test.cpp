#include <iostream>

#include "network/HostDiscovery.h"

int main()
{
    HostDiscovery discovery;

    std::string ipAddress = "127.0.0.1";

    std::cout << "Host Discovery Test\n";
    std::cout << "-------------------\n";

    bool reachable =
        discovery.isHostReachable(ipAddress);

    std::cout << "Host: "
              << ipAddress
              << "\n";

    if (reachable)
    {
        std::cout << "Status: Reachable\n";
    }
    else
    {
        std::cout << "Status: Not reachable\n";
    }

    Host host =
        discovery.discoverHost(ipAddress);

    std::cout << "Host object created for: "
              << host.getIpAddress()
              << "\n";

    return 0;
}