/*
 *  Implementation of standard module Time
 */



#include "Time.h"

/******************************************************************/


int SACisleap(int year)
{
  return((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0));
}



/******************************************************************/


int SACisleapt(time_t *t)
{
  struct tm *tt;
  int year;
  
  tt=localtime(t);
  year=tt->tm_year + 1900;
  
  return((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0));
}



/******************************************************************/


