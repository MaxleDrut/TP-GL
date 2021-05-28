#include <iostream>
#include <algorithm>
#include <vector>
#include "Terminal.h"
#include "utils/utils.h"

using namespace std;

[[noreturn]] void Terminal::start()
{
    cout << "Welcome to AirWatcher !" << endl;

    while(true)
    {
        if(userType == UserTypes::NONE)
        {
            cout << "Please authenticate." << endl;
            printAuthPrompt();
            cout << "Type 'help' to show a list of commands." << endl;
        }
        else
        {
            auto command = promptUser(selectedSensorId.empty() ? "" : "sensor " + selectedSensorId);
            bool cmdFound = selectedSensorId.empty() ? processCommand(command) : processSensorCommand(command);
            if(!cmdFound)
            {
                cout << "Invalid command. Type 'help' to get a list of available commands." << endl;
            }
        }
    }
}

void Terminal::printAuthPrompt()
{
    bool authSuccess = false;
    string login;
    string password;

    while(!authSuccess)
    {
        cout << "Login: ";
        cin >> login;
        cout << "Password: ";
        cin >> password;

        User *user = userService->authenticate(login, password);
        authSuccess = user != nullptr;
        
        cout << user << endl;

        return;

        if(authSuccess)
        {
            userId = login;
            userPassword = password;
            userType = userService->getPrivilege(user->getIdentifier());
            cout << "Connected as " << userId << "." << " (" << userType << ")" << endl;
        }
        else
        {
            cout << "Invalid credentials. Please retry." << endl;
        }
    }
}

vector<string> Terminal::promptUser(const string &prefix)
{
    string command;
    cout << LIGHT_BLUE;
    if(!prefix.empty())
        cout << "[" << prefix << "] ";
    cout << "$> " << NO_COLOR;
    getline(cin >> ws, command, '\n'); // ignoring previous spaces with ws ; prevents getline from breaking after using cin

    // Remove consecutive whitespaces
    std::string::iterator new_end = std::unique(
            command.begin(), command.end(),
            [](char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
    );
    command.erase(new_end, command.end());

    // Remove heading and trailing whitespaces
    if(command.find(' ') == 0)
        command.erase(0, 1);
    if(command.rfind(' ') == command.length() - 1)
        command.erase(command.end() - 1);

    debug(command);

    // Extract command tokens
    vector<string> commandTokens{};

    size_t pos = 0;
    while(pos < command.length())
    {
        size_t nextSpace = command.find(' ', pos);
        if(nextSpace == string::npos) // means there is no space until end of string
            nextSpace = command.length();

        string token = command.substr(pos, nextSpace - pos);
        commandTokens.push_back(token);

        pos = nextSpace + 1;
    }

    return commandTokens;
}


bool Terminal::processCommand(const vector<string>& command)
{
    if(command[0] == "use")
    {
        /* Handled commands:
         *  use sensor <id>
         *  --> select sensor for various functionalities
         */
        if(command.size() < 2) return false;

        if(command[1] == "sensor" && command.size() > 2)
        {
            string sensorId = command[2];

            // TODO get sensor

            selectedSensorId = sensorId;

            cout << "Selected sensor with id " << sensorId << "." << endl;
        }
        else
        {
            return false;
        }
    }
    else if(command[0] == "get")
    {
        /* Handled commands:
         *  get sensors
         *  --> show sensor list
         *
         * [PROV/GOV only]
         *  get cleaners
         *  --> show cleaners list, with status (active / inactive)
         *  (if gov, shows cleaners by provider)
         *
         * [PROV/GOV only]
         *  get cleaner <id>
         *  --> Displays cleaner info (provider, statistics)
         *
         * [GOV only]
         *  get users
         *  --> Displays the names of users and their sensors
         *
         * [GOV only]
         *  get providers
         *  --> Displays providers
         */
        if(command.size() < 2) return false;

        if(command[1] == "sensors")
        {
            // TODO
            cout << "Not implemented." << endl;
        }
        else if(command[1] == "cleaners" && (userType == UserTypes::GOVERNMENT || userType == UserTypes::PROVIDER))
        {
            // TODO
            cout << "Not implemented." << endl;
        }
        else if(command[1] == "cleaner" && command.size() > 2
                && (userType == UserTypes::GOVERNMENT || userType == UserTypes::PROVIDER))
        {
            // TODO
            cout << "Not implemented." << endl;
        }
        else if(command[1] == "users" && userType == UserTypes::GOVERNMENT)
        {
            // TODO
            cout << "Not implemented." << endl;
        }
        else if(command[1] == "providers" && userType == UserTypes::GOVERNMENT)
        {
            // TODO
            cout << "Not implemented." << endl;
        }
        else
        {
            return false;
        }
    }
    else if(command[0] == "airQ")
    {
        /* Handled commands:
         *  airQ <latitude> <longitude> <radius> <start> <end>
         *  --> Displays the mean quality of air in a specified area and period of time
         *  airQ <latitude> <longitude> <date>
         *  --> Displays the quality of air at a specific spot and time
         */
        if(command.size() == 6)
        {
            // TODO
            cout << "Not implemented." << endl;
        }
        else if(command.size() == 4)
        {
            // TODO
            cout << "Not implemented." << endl;
        }
        else
        {
            return false;
        }
    }
    else if(command[0] == "help")
    {
        /* Handled commands:
         *  help
         *  --> show this message
         */
        printUserMenu(userType);
    }
    else if(command[0] == "exit")
    {
        /* Handled commands:
         *  exit
         *  --> leave the application
         */
        cout << "Exiting the application. Bye !" << endl;
        exit(0);
    }
    else
    {
        return false;
    }

    return true;
}

bool Terminal::processSensorCommand(const vector<string> &command)
{
    if(command[0] == "measurements")
    {
        /* Handled commands:
         * measurements
         *  --> Display sensor last 10 measurements
         * measurements all
         *  --> Display all sensor measurements
         * measurements <date>
         *  --> Display sensor measurements for a given date
         */
        // TODO
        if(command.size() == 1)
        {
            // TODO measurements
            cout << "Not implemented." << endl;
        }
        else if(command[1] == "all")
        {
            // TODO measurements all
            cout << "Not implemented." << endl;
        }
        else
        {
            // TODO measurements <date> ; try parse date, print error if not possible
            cout << "Not implemented." << endl;
        }
    }
    else if(command[0] == "evaluate")
    {
        /* Handled commands:
         * evaluate
         *  --> Run malfunctioning sensor detection algorithm
         */
        // TODO
        cout << "Not implemented." << endl;
    }
    else if(command[0] == "disable")
    {
        /* Handled commands:
         * disable
         *  --> Disable this sensor. It won't be used in future computations.
         */
        // TODO
        cout << "Not implemented." << endl;
    }
    else if(command[0] == "enable")
    {
        /* Handled commands:
         * enable
         *  --> Enable this sensor (only if disabled)
         */
        // TODO
        cout << "Not implemented." << endl;
    }
    else if(command[0] == "compare")
    {
        /* Handled commands:
         * compare
         *  --> Display a similarity ranking between this sensor and the others
         */
        // TODO
        cout << "Not implemented." << endl;
    }
    else if(command[0] == "menu")
    {
        /* Handled commands:
         * menu
         *  --> Go back to main menu
         */
        selectedSensorId = "";
        cout << "Switched back to main menu." << endl;
    }
    else if(command[0] == "exit")
    {
        /* Handled commands:
         *  exit
         *  --> leave the application
         */
        cout << "Exiting the application. Bye !" << endl;
        exit(0);
    }
    else if(command[0] == "help")
    {
        /* Handled commands:
         * help
         *  --> Display this help message
         */
        printSensorMenu(userType);
    }
    else
    {
        return false;
    }

    return true;
}

void Terminal::printUserMenu(UserTypes privilegeLevel)
{
    cout << BOLD << "Available commands: " << NO_COLOR << endl;

    cout << PALE_BLUE << "use sensor <id>" << NO_COLOR << endl
        << " Select a sensor with the specified id and switches to sensor context." << endl;

    cout << PALE_BLUE << "get sensors" << NO_COLOR << endl << " Display sensor list." << endl;

    if(privilegeLevel == UserTypes::PROVIDER || privilegeLevel == UserTypes::GOVERNMENT)
    {
        cout << PALE_BLUE << "get cleaner <id>" << NO_COLOR << endl
            << " Display information about a cleaner with the specified id." << endl;
    }

    if(privilegeLevel == UserTypes::PROVIDER)
    {
        cout << PALE_BLUE << "get cleaners" << NO_COLOR << endl << " Display owned cleaners list." << endl;
    }
    else if(privilegeLevel == UserTypes::GOVERNMENT)
    {
        cout << PALE_BLUE << "get cleaners" << NO_COLOR << endl << " Display cleaners sorted by providers." << endl;
        cout << PALE_BLUE << "get users" << NO_COLOR << endl << " Display the names and sensors of users." << endl;
        cout << PALE_BLUE << "get providers" << NO_COLOR << endl << " Display providers." << endl;
    }

    cout << PALE_BLUE << "airQ <latitude> <longitude> <radius> <start_date> <end_date>" << NO_COLOR << endl
         << " Display the mean quality of air in the specified area, between start_date and end_date. "
         << "Dates should follow this format: dd/mm/yyyy. "
         << endl;

    cout << PALE_BLUE << "airQ <latitude> <longitude> <date>" << NO_COLOR << endl
         << " Display the quality of air at a specific point and time." << endl;

    cout << PALE_BLUE << "help" << NO_COLOR << endl << " Display this message." << endl;
    cout << TURQUOISE << "exit" << NO_COLOR << endl << " Close the application." << endl;


    /*
     * List of commands:
     *
     * use sensor <x>   ---> select sensor for various functionalities
     *  -> sensor menu
     *
     *
     * get sensors ---> show sensor list
     * [PROV/GOV] get cleaners
     * ---> show cleaners list, with status (active / inactive)
     *  (if gov, shows cleaners by provider)
     *
     * [PROV/GOV] get cleaner <X>
     * ---> Displays cleaner info (provider, statistics)
     *
     * [GOV] get users
     * ---> Displays the names of users and their sensors
     *
     * [GOV] get providers
     * ---> Displays providers
     *
     *
     * airQ <latitude> <longitude> <radius> <start> <end>
     * --> Displays the mean quality of air in a specified area and period of time
     * airQ <latitude> <longitude> <date>
     * ---> Displays the quality of air at a specific spot and time
     *
     * help --> show this message
     *
     */
}

void Terminal::printSensorMenu(UserTypes privilegeLevel)
{
    cout << BOLD << "You have selected sensor with id " << selectedSensorId << "." << endl;
    cout << "Available commands: " << NO_COLOR << endl;

    cout << PALE_BLUE << "measurements" << NO_COLOR << endl
        << " Display this sensor's last 10 measurements." << endl;
    cout << PALE_BLUE << "measurements all" << NO_COLOR << endl
        << " Display all measurements for this sensor." << endl;
    cout << PALE_BLUE << "measurements <date>" << NO_COLOR << endl
        << " Display this sensor's measurements for the specified date. Date should follow this format: dd/mm/yyyy." << endl;

    cout << PALE_BLUE << "evaluate" << NO_COLOR << endl
        << " Run malfunctioning sensor detection algorithm on this sensor." << endl;
    cout << PALE_BLUE << "disable" << NO_COLOR << endl
        << " Disable this sensor. It won't be used in future computations." << endl;
    cout << PALE_BLUE << "enable" << NO_COLOR << endl
        << " Enable this sensor to use it again in computations." << endl;
    cout << PALE_BLUE << "compare" << NO_COLOR << endl
        << " Display a similarity ranking between this sensor and the others." << endl;

    cout << PALE_BLUE << "help" << NO_COLOR << endl << " Display this help message." << endl;
    cout << TURQUOISE << "menu" << NO_COLOR << endl << " Go back to main menu." << endl;
    cout << TURQUOISE << "exit" << NO_COLOR << endl << " Exit the application." << endl;

    /*
     * List of commands:
     *
     * measurements
     *  --> Display sensor last 10 measurements
     * measurements all
     *  --> Display all sensor measurements
     * measurements <date>
     *  --> Display sensor measurements for a given date
     * evaluate
     *  --> Run malfunctioning sensor detection algorithm
     * disable
     *  --> Disable this sensor. It won't be used in future computations.
     * enable
     *  --> Enable this sensor (only if disabled)
     * compare
     *  --> Display a similarity ranking between this sensor and the others
     * help
     *  --> Display this help message
     * menu
     *  --> Go back to main menu
     * exit
     *  --> leave the application
     */
}

void Terminal::printSensors(const vector<Sensor> &sensors)
{

}

void Terminal::printAirQuality(double airQuality)
{

}

void Terminal::printIndividualUser(const IndividualUser *const user)
{

}

void Terminal::printCleaner(const Cleaner *const cleaner)
{

}

void Terminal::printMeasurement(const Measurement &measurement)
{

}