#include "Env.h"

/******************************************************************/


void UnsetEnv(char *envvar)
{
  static char buffer[100];
  
  strcpy(buffer, envvar);
  strcat(buffer, "=");
      
  putenv(buffer);
}


/******************************************************************/
