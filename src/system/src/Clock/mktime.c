/*
 *  Implementation of standard module Time
 */



#include "Time.h"

/******************************************************************/


time_t *SACmktime(int *success, int year, int mon, int day, 
						int hour, int min, int sec)
{
  struct tm t;
  time_t *res;
  
  t.tm_year=year;
  t.tm_mon=mon;
  t.tm_mday=day;
  t.tm_hour=hour;
  t.tm_min=min;
  t.tm_sec=sec;
  
  res=(time_t*)SAC_MALLOC(sizeof(time_t));

  *res=mktime(&t);

  if (*res<(time_t)0)
  {
	 *success=0;
  }
  else
  {
	 *success=1;
  }
  
  return(res);
}


/******************************************************************/


