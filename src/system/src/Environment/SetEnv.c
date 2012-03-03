#include "Env.h"

/******************************************************************/


int SetEnv(char *envvar, char *value, int overwrite)
{
  int res = 0;

  if (overwrite || (getenv(envvar) == NULL))
  {
#if HAVE_SETENV
    res = setenv(envvar, value, overwrite);
#else
    size_t size = strlen(envvar) + 1 + strlen(value) + 1;
    char* buf = (char*) SAC_MALLOC(size);
    strcpy(buf, envvar);
    strcat(buf, "=");
    strcat(buf, value);
    putenv(buf);
#endif
  }

  return (res);
}


/******************************************************************/
