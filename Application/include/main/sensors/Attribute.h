#pragma once

#include <String>

using namespace std;

class Attribute {
    private:
        string unit;
        string description;
        string identifier;
        
    public:
        Attribute(const string unit, const string desc, const string iden) : unit(unit), description(desc), identifier(iden) {};

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