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

extern long int random();

extern void srandom(unsigned seed);


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
  
  return((int)((n/(double)RAND_MAX) * (max-min+1) + min));
}


/********************************************************************/


double SACdrandom(double min, double max)
{
  long int n;
  
  do
  {
	 n=random();
  } 
  while (n==RAND_MAX);
  
  return((n/(double)RAND_MAX) * (max-min) + min);
}



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







