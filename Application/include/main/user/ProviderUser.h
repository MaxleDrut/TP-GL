#pragma once

#include <string>
#include <vector>

#include "User.h"
#include "Cleaner.h"

using namespace std;


class ProviderUser: User
{

private:
    vector<Cleaner> cleaners;
    
public:

    ProviderUser(string identifier, string password)
    {
        this->identifier = identifier;
        this->password = password;
    }

    virtual ~ProviderUser()
    {
        
    }

    vector<Cleaner> getCleaners()
    {
        return this->cleaners;
    }

    void addCleaner(Cleaner cleaner)
    {
        this->cleaners.push_back(cleaner);
    }

};
