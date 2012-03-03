#include "Env.h"

/******************************************************************/
/* functions to query the global variable "environ". */

extern char **environ;

int EnvCount()
{
  int i = 0;

  if (environ) {
    while (environ[i]) {
      ++i;
    }
  }

  return i;
}

char* IndexEnv(int i)
{
  char* res;
  int k = 0;

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
