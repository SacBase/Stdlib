/*
 * Implementation of standard module Time
 */

#include "Clock.h"

sac_int SACsec(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_sec);
}

sac_int SACmin(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_min);
}

sac_int SAChour(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_hour);
}

sac_int SACmday(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_mday);
}

sac_int SACmon(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_mon);
}

sac_int SACyear(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_year);
}

sac_int SACwday(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_wday);
}

int SACyday(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_yday);
}
