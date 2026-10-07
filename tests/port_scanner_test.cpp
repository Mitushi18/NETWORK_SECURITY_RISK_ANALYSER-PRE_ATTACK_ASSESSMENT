#include <iostream>
#include "network/PortScanner.h"

int main() {

    PortScanner scanner;

    // Use only a system/network that you are authorized to assess.
    std::string target = "127.0.0.1";

    std::cout << "Scanning target: "
              << target
              << std::endl;

    std::vector<int> openPorts =
        scanner.scanPorts(target, 1, 100);

    std::cout << std::endl;
    std::cout << "Open Ports" << std::endl;
    std::cout << "----------" << std::endl;

    if (openPorts.empty()) {
        std::cout << "No open ports found."
                  << std::endl;
    }
    else {
        for (int port : openPorts) {
            std::cout << "Port "
                      << port
                      << " is OPEN"
                      << std::endl;
        }
    }

    return 0;
}