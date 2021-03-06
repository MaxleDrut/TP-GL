#pragma once

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#define private public

#include "services/SensorService.h"
#include "sensors/Sensor.h"
#include "services/LoadService.h"

class SensorService_test {
    private:
        SensorService * service;

    public:
        SensorService_test();
        virtual ~SensorService_test();
        int test_getSensors();
        int test_getSensor();
        int test_FR5_malfunctioningAnalysis();
        int test_isGivenTimeInsideTimePeriod();
        int test_distanceBetweenPositions();
        int test_convertValuesAttributesToATMOScore();
        int test_FR8_quality();
        int test_FR8_qualityAttributes();
        int test_FR7_averageValue();
        int test_FR7_sensorComparison();
};
