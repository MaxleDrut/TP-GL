#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "user/Cleaner.h"

using namespace std;

class CleanerService
{


    private:
        vector<Cleaner> cleaners;

    public:
        CleanerService();
        virtual ~CleanerService();
        vector<Cleaner> getCleaners() const;
};