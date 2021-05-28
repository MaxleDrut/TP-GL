#pragma once

#include <string>
#include "user/User.h"
#include "user/IndividualUser.h"
#include "sensors/Sensor.h"
#include "sensors/Measurement.h"
#include "user/Cleaner.h"

#include "services/SensorService.h"
#include "services/CleanerService.h"
#include "services/UserService.h"

using namespace std;

class Terminal
{
private:
    string selectedSensorId;
    string userId;
    string userPassword;
    UserTypes userType;

    SensorService *sensorService;
    UserService *userService;
    CleanerService *cleanerService;

public:
    Terminal(SensorService *sensorService, UserService *userService, CleanerService *cleanerService): userType(UserTypes::NONE) {};

    [[noreturn]] void start();

private:
    void printAuthPrompt();
    void printSensors(const vector<Sensor>& sensors);
    void printMeasurement(const Measurement& measurement);
    void printAirQuality(double airQuality);
    void printIndividualUser(const IndividualUser * const user);
    void printUserMenu(UserTypes privilegeLevel);
    vector<string> promptUser(const string &prefix);
    bool processCommand(const vector<string>& command);
    void printSensorMenu(UserTypes privilegeLevel);
    bool processSensorCommand(const vector<string> &command);
    void printCleaner(const Cleaner * const cleaner);
};
