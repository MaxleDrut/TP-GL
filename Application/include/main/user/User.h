#pragma once

#include <string>
#include <iostream>

using namespace std;

enum UserTypes {
    INDIVIDUAL,
    PROVIDER,
    GOVERNMENT,
    NONE
};

class User
{
private:
    string identifier;
    string password;
    
public:
    User() = default;

    User(string &identifier, string &password): identifier(identifier), password(password) { cout << "------------- " << identifier << " " << password << endl; };

    virtual ~User() = default;

    virtual string getIdentifier() const
    {
        return identifier;
    }

    virtual string getPassword() const
    {
        return password;
    }
};
