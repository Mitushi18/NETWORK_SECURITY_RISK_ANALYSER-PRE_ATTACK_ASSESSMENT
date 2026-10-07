#include "network/ServiceDetector.h"

ServiceDetector::ServiceDetector()
{
}

void ServiceDetector::detectService(Port& port)
{
    int portNumber = port.getPortNumber();

    switch (portNumber)
    {
        case 21:
            port.setServiceName("FTP");
            break;

        case 22:
            port.setServiceName("SSH");
            break;

        case 23:
            port.setServiceName("Telnet");
            break;

        case 25:
            port.setServiceName("SMTP");
            break;

        case 53:
            port.setServiceName("DNS");
            break;

        case 80:
            port.setServiceName("HTTP");
            break;

        case 110:
            port.setServiceName("POP3");
            break;

        case 143:
            port.setServiceName("IMAP");
            break;

        case 443:
            port.setServiceName("HTTPS");
            break;

        case 445:
            port.setServiceName("SMB");
            break;

        case 3389:
            port.setServiceName("RDP");
            break;

        default:
            port.setServiceName("Unknown");
            break;
    }
}