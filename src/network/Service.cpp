#include "network/Service.h"

Service::Service(
    int port,
    const std::string& protocol,
    const std::string& name
)
    : portNumber(port),
      protocol(protocol),
      serviceName(name)
{
}

int Service::getPortNumber() const
{
    return portNumber;
}

std::string Service::getProtocol() const
{
    return protocol;
}

std::string Service::getServiceName() const
{
    return serviceName;
}