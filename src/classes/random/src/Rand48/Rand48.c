/*
 *  Implementation of standard class Rand48.
 */


#include <stdlib.h> 
#include <stdio.h>

#include "sac.h"


/********************************************************************/


extern void srand48(long int seed);

extern double drand48();


/********************************************************************/


void *Rand48Gen;


/********************************************************************/



void *create_Rand48Gen()
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


int *SACrand48array(int size, int min, int max)
{
  int i, *arr;
  
  arr=(int*)SAC_MALLOC(size*sizeof(int));
  
  for (i=0; i<size; i++)
  {
	 arr[i]=SACrand48(min, max);
  }
  
  return(arr);
}





/********************************************************************/


double *SACdrand48array(int size, double min, double max)
{
  int i;
  double *arr;
  
  arr=(double*)SAC_MALLOC(size*sizeof(double));
  
  for (i=0; i<size; i++)
  {
	 arr[i]=SACdrand48(min, max);
  }
  
  return(arr);
}


/********************************************************************/



