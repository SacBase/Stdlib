/*
 *  Implementation of external standard class CommandLine.
 */


#include "libsac.h"
#include "icm2c.h"



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


ComLine *create_TheCommandLine(int argc, char *argv[])
{
  ComLine *parameters;
  
  parameters=(ComLine *)MALLOC(sizeof(ComLine));
  
  parameters->argc=argc;
  parameters->argv=argv;
  
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
    result=(char*)MALLOC(strlen((TheCommandLine->argv)[n])+1);
  
    strcpy(result, (TheCommandLine->argv)[n]);
  }
  else
  {
    result=(char*)MALLOC(1);
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
  
  result=(char*)MALLOC(len+1+TheCommandLine->argc);

  strcpy(result, (TheCommandLine->argv)[0]);
  
  for (i=1; i<TheCommandLine->argc; i++)
  {
    strcat(result, " ");
    strcat(result, (TheCommandLine->argv)[i]);
  }
  
  return(result);
}


/*****************************************************/



