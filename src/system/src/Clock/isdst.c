/*
 *  Implementation of standard module Time
 */



#include "Clock.h"

/******************************************************************/


int SACisdst(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_isdst);
}


/******************************************************************/


