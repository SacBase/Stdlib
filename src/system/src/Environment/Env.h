/*
 *  implementation of standard module Env
 */


#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "sac.h"


#ifndef HAVE_PUTENV
extern int putenv(const char *);
#endif /* HAVE_PUTENV */

