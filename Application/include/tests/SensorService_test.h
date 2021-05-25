#pragma once

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Services/SensorService.h"
#include "sensors/Sensor.h"
#include "Services/LoadService.h"

class SensorService_test {
    private:
        SensorService * service;

    public:
        SensorService_test();
        virtual ~SensorService_test();
        int test_getSensors();
        int test_getSensor();

};
