//
// Created by Romain on 07/05/2021.
//

#pragma once

#include <string>

using namespace std;

class Terminal
{
private:
    string selectedSensorId;
    string userId;
    string userPassword;

public:
    Terminal(): selectedSensorId(nullptr), userId(nullptr), userPassword(nullptr);

    start();

private:
    printAuthPrompt();
    printSensors(const vector<Sensor> sensors);
    printMeasurement(const Measurement measurement);
    printAirQuality(double airQuality);
    printIndividualUser(const IndividualUser * const user);
    printUserMenu(UserTypes userType);
    promptUser();
    printSensorMenu(UserTypes userType);
    promptSensor();
    printCleaner(const Cleaner * const cleaner);
};
