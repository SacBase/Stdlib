/*
 * Implementation of standard module Time
 */

#include "Clock.h"

time_t *SACgettime( void)
{
    time_t *res = (time_t *)SAC_MALLOC(sizeof(time_t));
    time(res);
    return res;
}
