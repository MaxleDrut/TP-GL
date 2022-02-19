#pragma once
 
#include <assert.h>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

#include "services/SensorService.h"
#include "services/LoadService.h"

class AlgosSpeedTest
{
    private:
        SensorService * service;

    public:
        AlgosSpeedTest();
        virtual ~AlgosSpeedTest();
        void perf_FR8_AirQuality();
        void perf_FR5_Malfunction();
        void perf_FR7_SensorComparison();
};