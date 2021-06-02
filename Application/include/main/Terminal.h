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
    Terminal(SensorService *sensorService, UserService *userService, CleanerService *cleanerService): 
        sensorService(sensorService), userService(userService), cleanerService(cleanerService), userType(UserTypes::NONE) {};

    [[noreturn]] void start();

private:
    void printAuthPrompt();
    vector<string> promptUser(const string &prefix);

    void printUserMenu(UserTypes privilegeLevel) const;
    void printSensorMenu(UserTypes privilegeLevel) const;

    bool processCommand(const vector<string> &command);
    bool processSensorCommand(const vector<string> &command);

    void printSensors(const vector<Sensor*> &sensors) const;
    void printCleaners(const vector<Cleaner*> &cleaners) const;
    void printCleaner(const Cleaner * const cleaner) const;
    void printIndividualUsers(const vector<IndividualUser*> &users) const;
    void printProviders(const vector<ProviderUser*> &users) const;
    void printMeasurements(const vector<Measurement*> &measurements) const;

    void printMeasurement(const Measurement &measurement);
    void printSensorComparisonResults(const map<Sensor, double, SensorComparator> &results) const;
    void printAirQualityResults(const string &atmoIndicator) const;
};
