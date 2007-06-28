#include "sac.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void SAC__RUNTIMEERROR_error( int result, const char *message, ...)
{
  va_list arg_p;

  fprintf(stderr, "\n\n*** USER runtime error\n");
  fprintf(stderr, "*** ");

  va_start(arg_p, message);
  vfprintf(stderr, message, arg_p);
  va_end(arg_p);

  fprintf(stderr, "\n\n");

  exit(result);
}
