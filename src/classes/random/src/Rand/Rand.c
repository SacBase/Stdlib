/*
 *  Implementation of standard class Rand.
 */


#include <stdlib.h>
#include <stdio.h>

#include "sac.h"


/********************************************************************/

#ifndef RAND_MAX
#define RAND_MAX 2147483647
#endif
/*
 * Normally, RAND_MAX is defined in stdlib.h.
 * Unfortunatly, it's missing on some systems.
 */ 

/********************************************************************/


void *RandGen;

/********************************************************************/


void *create_RandGen()
{
  srand(1);
  
  return(NULL);
}



/********************************************************************/


int SACrand(int min, int max)
{
  int n;
  
  do
  {
	 n=rand();
  } 
  while (n==RAND_MAX);
  
  return((int)((n/(double)RAND_MAX) * (max-min+1) + min));
}

/********************************************************************/


int SACcrand()
{
  int n;

  n=rand();

  return( n);
}

/********************************************************************/


double SACdrand(double min, double max)
{
  int n;
  
  do
  {
	 n=rand();
  } 
  while (n==RAND_MAX);
  
  return((n/(double)RAND_MAX) * (max-min) + min);
}



/********************************************************************/



