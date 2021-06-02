

#include <sstream>
#include "services/CleanerService.h"
using namespace std;

CleanerService::CleanerService(vector<Cleaner *> &cleaners){
    this->cleaners=move(cleaners);
}

CleanerService::~CleanerService(){}


vector<Cleaner*> CleanerService::getCleaners() const{
    return cleaners;
}

Cleaner * CleanerService::getCleaner(const string &cleanerId) const 
{
    for(auto &cleaner : cleaners)
    {
        if(cleaner->getIdentifier() == cleanerId)
        {
            return cleaner;
        }
    }

    return nullptr;
}