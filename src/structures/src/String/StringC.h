/*
 *  Implementation of standard module StringC
 */


#include <string.h>
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "icm2c.h"
#include "libsac.h"


#ifdef CHECK

#ifndef MALLOC
#define MALLOC(size) __SAC__Runtime_malloc(size)
#endif   /* MALLOC  */

#define STRDUP(new, old) new=(string)MALLOC(strlen(old)+1);  \
                         strcpy(new, old);

#define RANGECHECK(check, lower, upper, str)									\
  if ((check<lower) || (check>upper))											\
    __SAC__Runtime_Error("Range violation upon string access:\n"		\
                         "tried to access character %d of string\n"	\
								 "\"%s\"", check, str);


#else  /* CHECK */

#define MALLOC(size) malloc(size)
#define STRDUP(new, old) new=strdup(old)
#define RANGECHECK(check, lower, upper, str)

#endif  /* CHECK */



typedef char* string;

