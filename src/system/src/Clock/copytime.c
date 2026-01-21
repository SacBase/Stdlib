/*
 * Implementation of standard module Time
 */

#include "Clock.h"

time_t *copy_time(time_t *t)
{
    time_t *res = (time_t *)SAC_MALLOC(sizeof(time_t));
    *res = *t;
    return res;
}
