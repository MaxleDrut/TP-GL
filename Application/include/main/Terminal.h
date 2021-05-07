#pragma once

#include <string>
#include "user/User.h"
#include "user/IndividualUser.h"
#include "sensors/Sensor.h"
#include "sensors/Measurement.h"
#include "user/Cleaner.h"

using namespace std;

class Terminal
{
private:
    string selectedSensorId;
    string userId;
    string userPassword;

public:
    Terminal(): selectedSensorId(nullptr), userId(nullptr), userPassword(nullptr) {};

    void start();

private:
    void printAuthPrompt();
    void printSensors(const vector<Sensor>& sensors);
    void printMeasurement(const Measurement& measurement);
    void printAirQuality(double airQuality);
    void printIndividualUser(const IndividualUser * const user);
    void printUserMenu(UserTypes userType);
    void promptUser();
    void printSensorMenu(UserTypes userType);
    void promptSensor();
    void printCleaner(const Cleaner * const cleaner);
};
