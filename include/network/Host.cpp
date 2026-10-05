#include "network/Host.h"

Host::Host(std::string ip) : ipAddress(ip) {}

void Host::setHostname(const std::string& name) {
    hostname = name;
}

std::string Host::getIpAddress() const {
    return ipAddress;
}

std::string Host::getHostname() const {
    return hostname;
}

void Host::addOpenPort(int port) {
    openPorts.push_back(port);
}

const std::vector<int>& Host::getOpenPorts() const {
    return openPorts;
}