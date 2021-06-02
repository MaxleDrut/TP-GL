
#include <string>
#include "user/User.h"

using namespace std;

string UserTypeToString(UserTypes &userType)
{
    if(userType == UserTypes::INDIVIDUAL) {
        return "INDIVIDUAL";
    }
    else if(userType == UserTypes::PROVIDER) {
        return "PROVIDER";
    }
    else if(userType == UserTypes::GOVERNMENT) {
        return "GOVERNMENT";
    }
    else {
        return "NONE";
    }
}