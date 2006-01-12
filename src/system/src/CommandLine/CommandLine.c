/*
 *  Implementation of external standard class CommandLine.
 */


#include <string.h>

#include "sac.h"


/*****************************************************/


typedef struct COMLINE
{
  int argc;
  char **argv;
}
ComLine;


/*****************************************************/


ComLine *TheCommandLine;


/*****************************************************/


ComLine *create_TheCommandLine()
{
  ComLine *parameters;
  
  parameters=(ComLine *)SAC_MALLOC(sizeof(ComLine));
  
  SAC_COMMANDLINE_GET( parameters->argc, parameters->argv);
  
  return(parameters);
}


/*****************************************************/


int SACargc()
{
  return(TheCommandLine->argc);
}


/*****************************************************/


char *SACargv(int n)
{
  char *result;
  
  if (n<TheCommandLine->argc)
  {
    result=(char*)SAC_MALLOC(strlen((TheCommandLine->argv)[n])+1);
  
    strcpy(result, (TheCommandLine->argv)[n]);
  }
  else
  {
    result=(char*)SAC_MALLOC(1);
    result[0]=0;
  }
  
  return(result);
}


/*****************************************************/


char *SACargvall()
{
  char *result;
  int len,i;
  
  len=0;
  
  for (i=0; i<TheCommandLine->argc; i++)
  {
    len += strlen(TheCommandLine->argv[i]);
  }
  
  result=(char*)SAC_MALLOC(len+1+TheCommandLine->argc);

  strcpy(result, (TheCommandLine->argv)[0]);
  
  for (i=1; i<TheCommandLine->argc; i++)
  {
    strcat(result, " ");
    strcat(result, (TheCommandLine->argv)[i]);
  }
  
  return(result);
}


/*****************************************************/





