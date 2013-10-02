/*
 *  Implementation of standard module Time
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



/******************************************************************/


time_t *SACstrptime(string * result, string s, string format)
{
  struct tm tt;
  string remain;
  time_t *t;

  t = (time_t *) SAC_MALLOC(sizeof(time_t));

  memset(&tt, 0, sizeof tt);
  remain = strptime(s, format, &tt);

  /* strptime() may return NULL if it fails to match all of the format string.
   * In that case an error occurred and the contents of tt is undefined.
   */
  if (remain == NULL) {
    *t = 0;
    *result = (string) SAC_MALLOC(1);
    **result = '\0';
  } else {
    *t = mktime(&tt);
    *result = (string) SAC_MALLOC(strlen(remain) + 1);
    strcpy(*result, remain);
  }

  return (t);
}



/******************************************************************/
