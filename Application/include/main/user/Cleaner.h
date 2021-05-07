#pragma once

#include <ctime>

class Cleaner
{
private:
    double latitude;
    double longitude;
    time_t start;
    time_t stop;

public:
    Cleaner(const double longi, const double lat, const time_t start, const time_t stop) : longitude(longi), latitude(lat), start(start), stop(stop) {}

    Cleaner() {
        longitude = latitude = 0.0;
        start = stop = NULL;
    }

    ~Cleaner() = default;

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