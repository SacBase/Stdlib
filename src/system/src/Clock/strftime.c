/*
 * Implementation of standard module Time
 */

#include "Clock.h"

string SACstrftime(sac_int len, string format, time_t *t)
{

    string res = (string)SAC_MALLOC((size_t)len + 1);
    res[0] = '\0';

    struct tm *tt = localtime(t);
    if (tt != NULL) {
        if (strftime(res, len, format, tt) == 0) {
            res[0] = '\0';
        }
    }

    return res;
}
