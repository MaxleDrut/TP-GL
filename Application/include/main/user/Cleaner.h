#pragma once

#include <ctime>
#include <string>

using namespace std;

class Cleaner
{
private:
    double latitude;
    double longitude;
    time_t start;
    time_t stop;
    string identifier;

public:
    Cleaner(const string id, const double longi, const double lat, const time_t start, const time_t stop) : identifier(id),longitude(longi), latitude(lat), start(start), stop(stop) {}
    Cleaner() {}

    ~Cleaner() = default;

    string getIdentifier() const{
        return identifier;
    }
    
    time_t getStart() const{
        return start;
    }

    time_t getStop() const {
        return stop;
    }

    double getLatitude() const {
        return latitude;
    }

    double getLongitude() const {
        return longitude;
    }
};