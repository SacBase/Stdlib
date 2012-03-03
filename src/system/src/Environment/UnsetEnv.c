#include "Env.h"

/******************************************************************/


void UnsetEnv(char *envvar)
{
#if HAVE_UNSETENV
  unsetenv(envvar);
#else
  putenv(envvar);
#endif
}


/******************************************************************/


