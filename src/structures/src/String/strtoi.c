/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

int SACstrtoi(string *remain, string input, int base)
{
  int res;
  char **rem;
  
  res=(int)strtol(input, rem, base);
  
  *remain=(string)RT_MALLOC(strlen(*rem)+1);
  strcpy(*remain, *rem);
  
  return(res);
}


/*****************************************************************/

int SACtoi(string input)
{
  return((int)strtol(input, NULL, 0));
}


/*****************************************************************/
