/*
 *  Implementation of standard class Rand48.
 */


#include <stdlib.h> 
#include <stdio.h>

#include "sac.h"


/********************************************************************/


extern void srand48(long int seed);

extern double drand48( void);


/********************************************************************/



void *create_Rand48Gen( void)
{
  srand48(1);
  
  return(NULL);
}



/********************************************************************/


int SACrand48(int min, int max)
{
  return((int)(drand48() * (max-min+1) + min));
}


/********************************************************************/


double SACdrand48(double min, double max)
{
  return(drand48() * (max-min) + min);
}


/********************************************************************/



