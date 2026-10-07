#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>
#include "network/Port.h"

class Host {
private:
    std::string ipAddress;
    std::string hostname;
    std::vector<Port> openPorts;

public:
    Host(std::string ip);

    void setHostname(const std::string& name);

    std::string getIpAddress() const;
    std::string getHostname() const;

    void addOpenPort(const Port& port);
    const std::vector<Port>& getOpenPorts() const;
};

#endif