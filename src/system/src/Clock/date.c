/*
 * Implementation of standard module Time
 */

#include "Clock.h"

sac_int SACdate(sac_int *mon, sac_int *day, time_t *t)
{
    struct tm *tt = localtime(t);
    *mon = (sac_int)(tt->tm_mon);
    *day = (sac_int)(tt->tm_mday);
    return (sac_int)(tt->tm_year);
}

sac_int SACclock(sac_int *min, sac_int *sec, time_t *t)
{
    struct tm *tt = localtime(t);
    *sec = (sac_int)(tt->tm_sec);
    *min = (sac_int)(tt->tm_min);
    return (sac_int)(tt->tm_hour);
}
