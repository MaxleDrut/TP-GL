#include "utils/utils.h"

string timestampToString(time_t &time)
{
    tm *ptm = localtime(&time);
    char buffer[64];
    strftime(buffer, 64, "%d/%m/%Y %H:%M:%S", ptm);

    return string(buffer);
}