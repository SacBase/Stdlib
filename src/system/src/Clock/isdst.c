/*
 * Implementation of standard module Time
 */

#include "Clock.h"

sac_int SACisdst(time_t *t)
{
    struct tm *tt = localtime(t);
    return (sac_int)(tt->tm_isdst);
}
