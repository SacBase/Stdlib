/*
 *  Implementation of standard module Time
 */



#include "Time.h"

/******************************************************************/

string SACstrftime(int len, string format, time_t *t)
{
  string result;
  struct tm *tt;
  
  tt=localtime(t);
  
  result=(string)SAC_MALLOC(len+1);
  
  strftime(result, len, format, tt);
  
  return(result);
}



/******************************************************************/

