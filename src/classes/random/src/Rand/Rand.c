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


int *SACrandarray(int size, int min, int max)
{
  int i, *arr;
  
  arr=(int*)SAC_MALLOC(size*sizeof(int));
  
  for (i=0; i<size; i++)
  {
	 arr[i]=SACrand(min, max);
  }
  
  return(arr);
}





/********************************************************************/


double *SACdrandarray(int size, double min, double max)
{
  int i;
  double *arr;
  
  arr=(double*)SAC_MALLOC(size*sizeof(double));
  
  for (i=0; i<size; i++)
  {
	 arr[i]=SACdrand(min, max);
  }
  
  return(arr);
}


/********************************************************************/


