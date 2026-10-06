#include "network/HostDiscovery.h"
#include "network/PortScanner.h"
#include "network/Port.h"
#include "network/ServiceDetector.h"
#include <cstdlib>
#include <string>
#include <vector>

HostDiscovery::HostDiscovery()
{
}

bool HostDiscovery::isHostReachable(
    const std::string& ipAddress
)
{
    std::string command =
        "ping -n 1 -w 1000 " + ipAddress + " > nul 2>&1";

    int result = std::system(command.c_str());

    return result == 0;
}

Host HostDiscovery::discoverHost(
    const std::string& ipAddress
)
{
    Host host(ipAddress);

    return host;
}

Host HostDiscovery::discoverHostWithPorts(
    const std::string& ipAddress,
    int startPort,
    int endPort
)
{
    Host host(ipAddress);

    // Check whether the host is reachable first.
    if (!isHostReachable(ipAddress))
    {
        return host;
    }

    // Scan the requested port range.
    PortScanner scanner;

    std::vector<int> openPorts =
        scanner.scanPorts(
            ipAddress,
            startPort,
            endPort
        );

    // Convert discovered port numbers into Port objects.
    ServiceDetector detector;

for (int portNumber : openPorts)
{
    Port port(
        portNumber,
        "TCP"
    );

    detector.detectService(port);

    host.addOpenPort(port);
}

    return host;
}