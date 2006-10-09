/*
 *  Implementation of standard module Time
 */



#include "Time.h"

/******************************************************************/


int SACdate(int *mon, int *day, time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  *mon=tt->tm_mon;
  *day=tt->tm_mday;
  
  return(tt->tm_year);
}



/******************************************************************/


int SACclock(int *min, int *sec, time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  *sec=tt->tm_sec;
  *min=tt->tm_min;
  
  return(tt->tm_hour);
}



/******************************************************************/
