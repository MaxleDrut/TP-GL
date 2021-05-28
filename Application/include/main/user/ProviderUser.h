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
    ProviderUser(string &identifier, string &password): User(identifier, password) {};

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
