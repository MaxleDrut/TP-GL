#pragma once

#include <string>

using namespace std;

class Attribute {
private:
    string unit;
    string description;
    string identifier;

public:
    Attribute(string &unit, string &desc, string &iden) : unit(unit), description(desc), identifier(iden) {};

    Attribute() {
        unit = description = identifier = nullptr;
    }

    virtual string getUnit() const {
        return unit;
    }

    virtual string getDescription() const {
        return description;
    }

    virtual string getIdentifier() const {
        return identifier;
    }
};