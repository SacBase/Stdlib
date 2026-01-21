#include "Env.h"

/******************************************************************/
/* functions to query the global variable "environ". */

extern char **environ;

sac_int EnvCount( void)
{
  sac_int i = 0;

  if (environ) {
    while (environ[i]) {
      ++i;
    }
  }

  return i;
}

char* IndexEnv( sac_int i)
{
  char* res;
  sac_int k = 0;

  if (environ) {
    while (k < i && environ[k]) {
      ++k;
    }
  }
  if (i != k || !environ || environ[k] == NULL) {
    res = (char*) SAC_MALLOC(1);
    *res = '\0';
  } else {
    res = (char*) SAC_MALLOC(strlen(environ[k]) + 1);
    strcpy(res, environ[k]);
  }

  return res;
}
