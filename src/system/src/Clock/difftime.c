/*
 *  Implementation of standard module Time
 */



#include "Time.h"

/******************************************************************/


double SACdifftime(time_t *t1, time_t *t2)
{
  return(difftime(*t1, *t2));
}


/******************************************************************/


