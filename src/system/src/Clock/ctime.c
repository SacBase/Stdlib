/*
 *  Implementation of standard module Time
 */



#include "Time.h"

/******************************************************************/


string SACctime(time_t *t)
{
  string buffer, result;
  
  buffer=ctime(t);
  
  result=(string)SAC_MALLOC(strlen(buffer)+1);
  strcpy(result, buffer);
  
  return(result);
}



/******************************************************************/


