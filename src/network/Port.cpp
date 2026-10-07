#include "network/Port.h"

Port::Port(int number, std::string protocol)
    : portNumber(number), protocol(protocol) {}

void Port::setServiceName(const std::string& service) {
    serviceName = service;
}

void Port::setServiceVersion(const std::string& version) {
    serviceVersion = version;
}

int Port::getPortNumber() const {
    return portNumber;
}

std::string Port::getProtocol() const {
    return protocol;
}

std::string Port::getServiceName() const {
    return serviceName;
}

std::string Port::getServiceVersion() const {
    return serviceVersion;
}