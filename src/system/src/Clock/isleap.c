/*
 * Implementation of standard module Time
 */

#include "Clock.h"

bool SACisleap(sac_int year)
{
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

bool SACisleapt(time_t *t)
{
    struct tm *tt = localtime(t);
    int year=tt->tm_year + 1900;
    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}
