#ifndef PORT_SCANNER_H
#define PORT_SCANNER_H

#include <string>
#include <vector>

class PortScanner
{
public:

    PortScanner();

    ~PortScanner();

    bool isPortOpen(
        const std::string& ipAddress,
        int port
    );

    std::vector<int> scanPorts(
        const std::string& ipAddress,
        int startPort,
        int endPort
    );
};

#endif