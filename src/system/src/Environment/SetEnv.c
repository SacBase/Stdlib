#include "Env.h"

/******************************************************************/


int SetEnv(char *envvar, char *value, int overwrite)
{
  int res=0;
  static char buffer[500];
  
  if (overwrite || (getenv(envvar)==NULL))
  {
    strcpy(buffer, envvar);
    strcat(buffer, "=");
    strcat(buffer, value);
    
    res=putenv(buffer);
  }
  
  return(res);
}


/******************************************************************/

