#include "Clock.h"

time_t *SACto_time( int secs)
{
    time_t *res = (time_t *)SAC_MALLOC(sizeof(time_t));
    *res = (time_t)secs;
    return res;
}
