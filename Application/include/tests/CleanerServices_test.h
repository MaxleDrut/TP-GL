#pragma once
 
#include <assert.h>
#include <iostream>
using namespace std;

#include "services/CleanerService.h"

class CleanerServices_test
{
    private:
        CleanerService * cleaner;

    public:
        CleanerServices_test();
        virtual ~CleanerServices_test();
};