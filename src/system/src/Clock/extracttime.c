/*
 *  Implementation of standard module Time
 */



#include "Time.h"

/******************************************************************/


int SACsec(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_sec);
}


/******************************************************************/


int SACmin(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_min);
}


/******************************************************************/


int SAChour(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_hour);
}


/******************************************************************/


int SACmday(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_mday);
}


/******************************************************************/


int SACmon(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_mon);
}



/******************************************************************/


int SACyear(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_year);
}



/******************************************************************/


int SACwday(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_wday);
}



/******************************************************************/


int SACyday(time_t *t)
{
  struct tm *tt;
  
  tt=localtime(t);
  
  return(tt->tm_yday);
}



/******************************************************************/


