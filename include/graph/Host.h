#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>

class Host {
private:
    std::string ipAddress;
    std::string hostname;
    std::vector<int> openPorts;

public:
    Host(std::string ip);

    void setHostname(const std::string& name);

    std::string getIpAddress() const;
    std::string getHostname() const;

    void addOpenPort(int port);
    const std::vector<int>& getOpenPorts() const;
};

#endif