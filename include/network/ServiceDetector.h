#ifndef SERVICE_DETECTOR_H
#define SERVICE_DETECTOR_H

#include "network/Port.h"

class ServiceDetector
{
public:
    ServiceDetector();

    void detectService(Port& port);
};

#endif