/*
 * Implementation of standard module Time
 */

#include "Clock.h"

extern char *strptime(const char *, const char *, struct tm *);

/*
 * Unfortunately, the function strptime() is not declared in time.h !
 * Fortunately, the standard library libc.a contains an implementation
 * of  strptime().
 *
 * bro: Actually, time.h does have a prototype for strptime(), but
 * then _XOPEN_SOURCE must be defined before including time.h.
 */

time_t *SACstrptime(string *res, string s, string format)
{
    time_t *t = (time_t *) SAC_MALLOC(sizeof(time_t));

    struct tm tt;
    memset(&tt, 0, sizeof tt);
    string remain = strptime(s, format, &tt);

    /* strptime() may return NULL if it fails to match all of the format string.
    * In that case an error occurred and the contents of tt is undefined.
    */
    if (remain == NULL) {
        *t = 0;
        *res = (string)SAC_MALLOC(1);
        **res = '\0';
    } else {
        *t = mktime(&tt);
        *res = (string)SAC_MALLOC(strlen(remain) + 1);
        strcpy(*res, remain);
    }

    return t;
}
