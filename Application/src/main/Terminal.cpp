#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include <chrono>
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

        if(authSuccess)
        {
            userId = login;
            userPassword = password;
            userType = userService->getPrivilege(user->getIdentifier());
            cout << BOLD << "Logged in as " << userId << "." << " (" << UserTypeToString(userType) << ")" << NO_COLOR << endl;
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

            Sensor *sensor = sensorService->getSensor(sensorId);
            if(sensor != nullptr)
            {
                selectedSensorId = sensorId;
                cout << "Selected sensor with id " << sensorId << "." << endl;
            }
            else
            {
                cout << RED << "No sensor with id " << sensorId << "." << NO_COLOR << endl;
            }
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
         *  --> Displays the names of individual users and their sensors
         *
         * [GOV only]
         *  get providers
         *  --> Displays providers
         */
        if(command.size() < 2) return false;

        if(command[1] == "sensors")
        {
            auto sensors = sensorService->getSensors();
            printSensors(sensors);
        }
        else if(command[1] == "cleaners")
        {
            if(userType == UserTypes::GOVERNMENT)
            {
                auto cleaners = cleanerService->getCleaners();
                printCleaners(cleaners);
            }
            else if(userType == UserTypes::PROVIDER)
            {
                auto user = userService->authenticate(userId, userPassword);
                auto provider = dynamic_cast<ProviderUser*>(user);

                auto cleaners = provider->getCleaners();
                printCleaners(cleaners);
            }
            else
            {
                return false;
            }
        }
        else if(command[1] == "cleaner" && command.size() > 2
                && (userType == UserTypes::GOVERNMENT || userType == UserTypes::PROVIDER))
        {
            string cleanerId = command[2];
            auto cleaner = cleanerService->getCleaner(cleanerId);
            
            if(cleaner != nullptr)
            {
                printCleaner(cleaner);
            }
            else
            {
                cout << RED << "No cleaner with id " << cleanerId << "." << NO_COLOR << endl;
            }
        }
        else if(command[1] == "users" && userType == UserTypes::GOVERNMENT)
        {
            auto users = userService->getIndividualUsers();
            printIndividualUsers(users);
        }
        else if(command[1] == "providers" && userType == UserTypes::GOVERNMENT)
        {
            auto providers = userService->getProviderUsers();
            printProviders(providers);
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
            cout << "Not implemented." << endl;
        }
        else if(command.size() == 4)
        {
            double latitude = stod(command[1]);
            double longitude = stod(command[2]);
            
            tm date = {};
            istringstream rqTimeStreamDate(command[3]);
            rqTimeStreamDate >> get_time(&date, "%d/%m/%Y");

            time_t date_timet = mktime(&date);

            auto quality = sensorService->FR8_quality(latitude, longitude, date_timet);
            printAirQualityResults(quality);
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
    else if(command[0] == "logout")
    {
        /* Handled commands:
         *  logout 
         *  --> Disconnect from current user session
         */
        userId = "";
        userPassword = "";
        userType = UserTypes::NONE;

        cout << BOLD << "You were successfully disconnected!" << NO_COLOR << endl;
    }
    else if(command[0] == "exit")
    {
        /* Handled commands:
         *  exit
         *  --> leave the application
         */
        cout << BOLD << "Exiting the application. Bye !" << NO_COLOR << endl;
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
    auto sensor = sensorService->getSensor(selectedSensorId);
    if(sensor == nullptr)
    {
        cout << RED << "Error retrieving selected sensor. Leaving sensor mode." << NO_COLOR << endl;
        selectedSensorId = "";
        return true;
    }

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
        
        auto measurements = sensor->getMeasurements();

        if(command.size() == 1) // last 10 measurements
        {
            vector<Measurement*> lastMeasurements{};

            auto it = measurements.rbegin();
            int cpt = 10;
            while(cpt > 0 && it != measurements.rend())
            {
                lastMeasurements.push_back(*it);
                it++;
                cpt--;
            }

            cout << "Last 10 measurements :" << endl;
            printMeasurements(lastMeasurements);
        }
        else if(command[1] == "all")
        {
            printMeasurements(measurements);
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
        auto begin_time = chrono::steady_clock::now();
        double score = sensorService->FR5_malfunctioningAnalysis(*sensor);        
        auto end_time = chrono::steady_clock::now();

        cout << "Divergence = " << score << " (elapsed time: " << chrono::duration_cast<chrono::milliseconds>(end_time - begin_time).count() << " ms)" << endl;
    }
    else if(command[0] == "disable" && userType == UserTypes::GOVERNMENT)
    {
        /* Handled commands:
         * disable
         *  --> Disable this sensor. It won't be used in future computations.
         */
        sensor->setReliable(false);

        cout << BOLD << "Sensor disabled." << NO_COLOR << endl;
    }
    else if(command[0] == "enable" && userType == UserTypes::GOVERNMENT)
    {
        /* Handled commands:
         * enable
         *  --> Enable this sensor (only if disabled)
         */
        sensor->setReliable(true);

        cout << BOLD << "Sensor enabled." << NO_COLOR << endl;
    }
    else if(command[0] == "compare" && command.size() >= 3)
    {
        /* Handled commands:
         * compare <start> <end>
         *  --> Display a similarity ranking between this sensor and the others
         */
        string startDateStr = command[1];
        string endDateStr = command[2];

        tm startDate = {};
        istringstream rqTimeStreamDate1(startDateStr);
        rqTimeStreamDate1 >> get_time(&startDate, "%d/%m/%Y");

        tm endDate = {};
        istringstream rqTimeStreamDate2(endDateStr);
        rqTimeStreamDate2 >> get_time(&endDate, "%d/%m/%Y");

        time_t startTime = mktime(&startDate);
        time_t endTime = mktime(&endDate);

        map<Sensor, double, SensorComparator> result = sensorService->FR7_sensorComparison(*sensor, startTime, endTime);
        printSensorComparisonResults(result);
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
        cout << BOLD << "Exiting the application. Bye !" << NO_COLOR << endl;
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

void Terminal::printUserMenu(UserTypes privilegeLevel) const
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
    cout << TURQUOISE << "logout" << NO_COLOR << endl << " Disconnect from current user session." << endl;
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
     * logout --> Disconnect from current user session.
     *
     */
}

void Terminal::printSensorMenu(UserTypes privilegeLevel) const
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

    if(privilegeLevel == UserTypes::GOVERNMENT)
    {
        cout << PALE_BLUE << "disable" << NO_COLOR << endl
            << " Disable this sensor. It won't be used in future computations." << endl;
        cout << PALE_BLUE << "enable" << NO_COLOR << endl
            << " Enable this sensor to use it again in computations." << endl;
    }
    
    cout << PALE_BLUE << "compare <start_date> <end_date>" << NO_COLOR << endl
        << " Display a similarity ranking between this sensor and the others during a specified time period. Dates should follow this format: dd/mm/yyyy." << endl;

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

void Terminal::printSensors(const vector<Sensor *> &sensors) const
{
    cout << "Registered sensors :" << endl;
    for(auto &sensor : sensors)
    {
        cout << "Sensor{id=" << sensor->getIdentifier() 
             << ", latitude=" << sensor->getLatitude() 
             << ", longitude=" << sensor->getLongitude() 
             << ", reliable=" << (sensor->getReliable() ? "yes" : "no")
             << "}" << endl;
    }
    cout << sensors.size() << " sensor" << (sensors.size() != 1 ? "s" : "") << " printed." << endl;
}

void Terminal::printCleaners(const vector<Cleaner*> &cleaners) const
{
    cout << "Registered cleaners :" << endl;
    for(auto &cleaner : cleaners)
    {
        auto start_time = cleaner->getStart();
        auto stop_time = cleaner->getStop();

        cout << "Cleaner{id=" << cleaner->getIdentifier()
             << ", latitude=" << cleaner->getLatitude() 
             << ", longitude=" << cleaner->getLongitude() 
             << ", start_date=" << timestampToString(start_time)
             << ", stop_date=" << timestampToString(stop_time)
             << "}" << endl;
    }
    cout << cleaners.size() << " cleaner" << (cleaners.size() != 1 ? "s" : "") << " printed." << endl;
}

void Terminal::printCleaner(const Cleaner *const cleaner) const
{
    cout << "Cleaner (id " << cleaner->getIdentifier() << "): " << endl;
    cout << "   Position: lat=" << cleaner->getLatitude() << " long=" << cleaner->getLongitude() << endl;
    
    auto start_time = cleaner->getStart();
    auto stop_time = cleaner->getStop();
    cout << "   Uptime period: " << timestampToString(start_time) << " to " << timestampToString(stop_time) << endl;
}

void Terminal::printIndividualUsers(const vector<IndividualUser*> &users) const
{
    cout << "List of individual users: " << endl;
    for(auto &user : users)
    {
        cout << TURQUOISE << "ID: " << user->getIdentifier() << NO_COLOR << endl;
        cout << user->getSensors().size() << " sensor(s) registered." << endl;
        if(user->getSensors().size() > 0)
        {
            cout << "Sensors: " << endl;
            for(auto &sensor : user->getSensors())
            {
                cout << "Sensor{id=" << sensor->getIdentifier() 
                     << ", latitude=" << sensor->getLatitude() 
                     << ", longitude=" << sensor->getLongitude() 
                     << ", reliable=" << (sensor->getReliable() ? "yes" : "no")
                     << "}" << endl;
            }
        }
        cout << endl;
    }

    cout << users.size() << " user" << (users.size() != 1 ? "s" : "") << " printed." << endl;
}

void Terminal::printProviders(const vector<ProviderUser*> &providers) const
{
    cout << "Registered providers: " << endl;
    for(auto &provider : providers)
    {
        cout << TURQUOISE << "ID: " << provider->getIdentifier() << NO_COLOR << endl;
        cout << provider->getCleaners().size() << " cleaner(s) registered." << endl;
        if(provider->getCleaners().size() > 0)
        {
            cout << "Cleaners: " << endl;
            for(auto &cleaner : provider->getCleaners())
            {
                cout << "Cleaner (id " << cleaner->getIdentifier() << "): " << endl;
                cout << "   Position: lat=" << cleaner->getLatitude() << " long=" << cleaner->getLongitude() << endl;

                auto start_time = cleaner->getStart();
                auto stop_time = cleaner->getStop();
                cout << "   Uptime period: " << timestampToString(start_time) << " to " << timestampToString(stop_time) << endl;
            }
        }
        cout << endl;
    }

    cout << providers.size() << " provider" << (providers.size() != 1 ? "s" : "") << " printed." << endl;
}

void Terminal::printMeasurements(const vector<Measurement*> &measurements) const
{
    for(auto &measurement : measurements)
    {
        auto timestamp = measurement->getTimestamp();
        cout << timestampToString(timestamp) << ": " 
            << measurement->getAttribute()->getIdentifier() << "=" 
            << measurement->getValue() << " " << measurement->getAttribute()->getUnit() 
            << endl;
    }
}

// TODO memcopy for each sensors : smells like sh*t to me
void Terminal::printSensorComparisonResults(const map<Sensor, double, SensorComparator> &results) const
{
    cout << "Similarity with sensor: " << endl;
    for(auto &result : results)
    {
        cout << "with " << result.first.getIdentifier() << ": " << (result.second * 100) << "%" << endl;
    }
}

void Terminal::printAirQualityResults(const string &atmoIndicator) const
{
    cout << "Air quality: " << atmoIndicator << endl;
}
