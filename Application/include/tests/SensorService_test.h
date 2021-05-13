#pragma once

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Services/SensorService.h"
#include "sensors/Sensor.h"

class SensorService_test {
    public:
        int test_loadCSV(string & file);

};
