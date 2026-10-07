#ifndef SERVICE_H
#define SERVICE_H

#include <string>

class Service
{
private:
    int portNumber;
    std::string protocol;
    std::string serviceName;

public:
    Service(
        int port,
        const std::string& protocol,
        const std::string& name
    );

    int getPortNumber() const;
    std::string getProtocol() const;
    std::string getServiceName() const;
};

#endif