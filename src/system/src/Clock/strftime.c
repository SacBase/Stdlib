/*
 *  Implementation of standard module Time
 */



#include "Clock.h"

/******************************************************************/

string SACstrftime(int len, string format, time_t* t)
{
  string result;
  struct tm *tt;

  result = (string) SAC_MALLOC(len + 1);
  result[0] = '\0';

  tt = localtime(t);
  if (tt != NULL) {
      if (strftime(result, len, format, tt) == 0) {
          result[0] = '\0';
      }
  }

  return (result);
}



/******************************************************************/
