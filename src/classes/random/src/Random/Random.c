/*
 *  Implementation of standard class Random.
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



/********************************************************************/


void *RandomGen;



/********************************************************************/



void *create_RandomGen()
{
  srandom(1);
  
  return(NULL);
}



/********************************************************************/


int SACrandom(int min, int max)
{
  long int n;
  
  do
  {
     n=random();
  } 
  while (n==RAND_MAX);
  
  return((int)(((n%RAND_MAX)/(double)RAND_MAX) * (max-min+1) + min));
}

/*
 * The modulo operation in the above line is required due to a very special
 * Solaris 7 feature:
 * While the libc function random expects RAND_MAX to be 2147483647,
 * stdlib.h defines RAND_MAX to be 32768. Without caution this results
 * in a rather undesired behaviour.
 */

/********************************************************************/


double SACdrandom(double min, double max)
{
  long int n;
  
  do
  {
	 n=random();
  } 
  while (n==RAND_MAX);
  
  return(((n%RAND_MAX)/(double)RAND_MAX) * (max-min) + min);
}

/*
 * The modulo operation in the above line is required due to a very special
 * Solaris 7 feature:
 * While the libc function random expects RAND_MAX to be 2147483647,
 * stdlib.h defines RAND_MAX to be 32768. Without caution this results
 * in a rather undesired behaviour.
 */



/********************************************************************/


int *SACrandomarray(int size, int min, int max)
{
  int i, *arr;
  
  arr=(int*)SAC_MALLOC(size*sizeof(int));
  
  for (i=0; i<size; i++)
  {
	 arr[i]=SACrandom(min, max);
  }
  
  return(arr);
}





/********************************************************************/


double *SACdrandomarray(int size, double min, double max)
{
  int i;
  double *arr;
  
  arr=(double*)SAC_MALLOC(size*sizeof(double));
  
  for (i=0; i<size; i++)
  {
	 arr[i]=SACdrandom(min, max);
  }
  
  return(arr);
}


/********************************************************************/








