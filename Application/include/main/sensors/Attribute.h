#pragma once

#include <string>

using namespace std;

class Attribute {
private:
    string unit;
    string description;
    string identifier;

public:
    Attribute(string const &unit, string const &desc, string const &iden) : unit(unit), description(desc), identifier(iden) {};

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

class AttributeComparator
{
public:
    bool operator() (const Attribute &a1, const Attribute &a2) const {
        return a1.getIdentifier() < a2.getIdentifier();
    }
    // ex: map<Attribute, double, AttributeComparator> mapAttributeDouble;
};
