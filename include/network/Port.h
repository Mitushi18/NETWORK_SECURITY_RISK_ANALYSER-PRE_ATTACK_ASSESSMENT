#ifndef PORT_H
#define PORT_H

#include <string>

class Port {
private:
    int portNumber;
    std::string protocol;
    std::string serviceName;
    std::string serviceVersion;

public:
    Port(int number, std::string protocol);

    void setServiceName(const std::string& service);
    void setServiceVersion(const std::string& version);

    int getPortNumber() const;
    std::string getProtocol() const;
    std::string getServiceName() const;
    std::string getServiceVersion() const;
};

#endif