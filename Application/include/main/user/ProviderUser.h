#pragma once

#include <string>
#include <vector>

#include "user/User.h"
#include "user/Cleaner.h"

using namespace std;


class ProviderUser: public User
{
private:
    vector<Cleaner *> cleaners;
public:
    ProviderUser(string &identifier, string &password)
    {
        this->identifier = identifier;
        this->password = password;
    }

    virtual ~ProviderUser() = default;

    vector<Cleaner *> getCleaners()
    {
        return this->cleaners;
    }

    void addCleaner(Cleaner * cleaner)
    {
        this->cleaners.push_back(cleaner);
    }
};
