#include <iostream>

#include "network/Host.h"
#include "network/Port.h"

int main() {

    // Create a host
    Host host("192.168.1.10");

    // Set hostname
    host.setHostname("test-machine");

    // Create SSH port
    Port sshPort(22, "TCP");
    sshPort.setServiceName("SSH");
    sshPort.setServiceVersion("OpenSSH 9.2");

    // Create HTTP port
    Port httpPort(80, "TCP");
    httpPort.setServiceName("HTTP");
    httpPort.setServiceVersion("Apache 2.4");

    // Add ports to the host
    host.addOpenPort(sshPort);
    host.addOpenPort(httpPort);

    // Display host information
    std::cout << "Host Information" << std::endl;
    std::cout << "----------------" << std::endl;

    std::cout << "IP Address: "
              << host.getIpAddress()
              << std::endl;

    std::cout << "Hostname: "
              << host.getHostname()
              << std::endl;

    std::cout << std::endl;

    // Display port information
    std::cout << "Open Ports" << std::endl;
    std::cout << "----------" << std::endl;

    for (const Port& port : host.getOpenPorts()) {

        std::cout << "Port: "
                  << port.getPortNumber()
                  << std::endl;

        std::cout << "Protocol: "
                  << port.getProtocol()
                  << std::endl;

        std::cout << "Service: "
                  << port.getServiceName()
                  << std::endl;

        std::cout << "Version: "
                  << port.getServiceVersion()
                  << std::endl;

        std::cout << std::endl;
    }

    return 0;
}