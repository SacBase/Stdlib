/*
 *  Implementation of standard module StringC
 */


#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "sac.h"


#ifdef CHECK

#define RANGECHECK(check, lower, upper, str)                    \
  if ((check<lower) || (check>upper))                           \
    SAC_RuntimeError("Range violation upon string access:\n"    \
                     "tried to access character %d of string\n" \
                     "\"%s\"", check, str);


#else  /* CHECK */

#define RANGECHECK(check, lower, upper, str)

#endif  /* CHECK */


#define STRDUP(new, old) new=(string)SAC_MALLOC(strlen(old)+1);  \
                         strcpy(new, old);

typedef char* string;
