/*
 *  implementation of external standard module SysErr
 */


#include <stdio.h>
#include <string.h>

#include "sac.h"


/*****************************************************************/

extern char *strerror(int num);


/*****************************************************************/


char *SACstrerror(int num)
{
  char *buffer, *result;
  
  buffer=strerror(num);
  
  result=(char *)SAC_MALLOC(strlen(buffer)+1);
  strcpy(result, buffer);
  
  return(result);
}

/*****************************************************************/


