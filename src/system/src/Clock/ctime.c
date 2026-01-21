/*
 * Implementation of standard module Time
 */

#include "Clock.h"

string SACctime(time_t *t)
{
    string buf, res;
    buf = ctime(t);
    res = (string)SAC_MALLOC(strlen(buf)+1);
    strcpy(res, buf);
    return res;
}
