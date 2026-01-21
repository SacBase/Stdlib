/*
 * Implementation of standard module Time
 */

#include "Clock.h"

time_t *SACmktime(bool *success,
                  sac_int year, sac_int mon, sac_int day,
						      sac_int hour, sac_int min, sac_int sec)
{
    struct tm t;
    t.tm_year = year;
    t.tm_mon = mon;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = sec;

    time_t *res = (time_t *)SAC_MALLOC(sizeof(time_t));
    *res = mktime(&t);

    *success = (*res < (time_t)0) ? 0 : 1;

    return res;
}
