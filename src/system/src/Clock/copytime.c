/*
 *  Implementation of standard module Time
 */



#include "Time.h"


/******************************************************************/


time_t *copy_time(time_t *t)
{
  time_t *res;
  
  res=(time_t*)MALLOC(sizeof(time_t));
  *res=*t;
  return(res);
}


/******************************************************************/
