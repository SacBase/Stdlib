#include "Env.h"

/******************************************************************/


int ExistEnv(char *envvar)
{
  return(getenv(envvar) == NULL);
}



