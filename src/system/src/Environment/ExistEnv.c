#include "Env.h"

/******************************************************************/


int ExistEnv(char *envvar)
{
  return((int)getenv(envvar));
}



