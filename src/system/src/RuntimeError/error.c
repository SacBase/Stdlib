#include "sac.h"
#include "sacinterface.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void SAC__RUNTIMEERROR_error(sac_int status, const char *msg, ...)
{
    va_list arg_p;

    fprintf(stderr, "\n\n*** USER runtime error\n");
    fprintf(stderr, "*** ");

    va_start(arg_p, msg);
    vfprintf(stderr, msg, arg_p);
    va_end(arg_p);

    fprintf(stderr, "\n\n");

    exit((int)status);
}
