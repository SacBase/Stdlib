/*
 *  implementation of standard module Env
 */


#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "libsac.h"
#include "icm2c.h"


#ifndef HAVE_PUTENV
extern int putenv(const char *);
#endif /* HAVE_PUTENV */
