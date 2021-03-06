#include <iostream>
#include <string>

/*#include "Terminal.h"
#include "services/LoadService.h"
#include "services/SensorService.h"
#include "services/CleanerService.h"
#include "services/UserService.h"
#include "utils/utils.h"*/

#include "../../include/main/Terminal.h"
#include "../../include/main/services/LoadService.h"
#include "../../include/main/services/SensorService.h"
#include "../../include/main/services/CleanerService.h"
#include "../../include/main/services/UserService.h"
#include "../../include/main/utils/utils.h"

using namespace std;

SensorService *sensorService;
UserService *userService;
CleanerService *cleanerService;


void loadApp()
{
    cout << GREY << "Loading app data files... ";

    string userFile = "res/dataset/users.csv";
    string providersFile = "res/dataset/providers.csv";
    string governmentFile = "res/dataset/government.csv";
    string passwordsFile = "res/dataset/passwords.csv";
    string cleanersFile = "res/dataset/cleaners.csv";
    string sensorsFile = "res/dataset/sensors.csv";
    string measurementsFile = "res/dataset/measurements.csv";
    string attributesFile = "res/dataset/attributes.csv";

    LoadService *loadService = new LoadService();
    loadService->loadCSV(
        userFile,             // User file
        providersFile,        // Providers file
        governmentFile,       // Government users file
        passwordsFile,        // Passwords file
        cleanersFile,         // Cleaners file
        sensorsFile,          // Sensors file
        measurementsFile,     // Measurements file
        attributesFile        // Attributes file
    );

    cout << "DONE" << endl;

    cout << loadService->getUsers().size() << " users, ";
    cout << loadService->getSensors().size() << " sensors, ";
    cout << loadService->getAttributes().size() << " attributes, ";
    cout << loadService->getMeasurements().size() << " measurements and ";
    cout << loadService->getCleaners().size() << " cleaners loaded." << endl;

    cout << GREY << "Creating service objects... ";

    auto sensors = loadService->getSensors();
    auto attributes = loadService->getAttributes();
    auto users = loadService->getUsers();
    auto cleaners = loadService->getCleaners();

    sensorService = new SensorService(attributes, sensors);
    userService = new UserService(std::move(loadService->getUsers()));
    cleanerService = new CleanerService(cleaners);

    cout << "DONE" << NO_COLOR << endl;
}

void startUserInterface()
{
    cout << GREY << "Starting terminal..." << NO_COLOR << endl;

    Terminal terminal(sensorService, userService, cleanerService);
    terminal.start();
}


int main()
{
    loadApp();
    startUserInterface();
    return 0;
}