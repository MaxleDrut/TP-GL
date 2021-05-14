

#include <sstream>
#include "services/CleanerService.h"
using namespace std;

CleanerService::CleanerService(){}

CleanerService::~CleanerService(){}


vector<Cleaner> CleanerService::getCleaners() const{
    return cleaners;
}