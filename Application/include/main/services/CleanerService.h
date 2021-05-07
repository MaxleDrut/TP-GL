#pragma once

#include <string>
using namespace std;

class CleanerController() {
    public:
        CleanerController() {}
        virtual ~CleanerController() {}

        bool loadCSV(string file);
};