#ifndef HOST_DISCOVERY_H
#define HOST_DISCOVERY_H

#include <string>
#include "network/Host.h"

class HostDiscovery
{
public:
    HostDiscovery();

    bool isHostReachable(const std::string& ipAddress);

    Host discoverHost(const std::string& ipAddress);

    Host discoverHostWithPorts(
        const std::string& ipAddress,
        int startPort,
        int endPort
    );
};

#endif