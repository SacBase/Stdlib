/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

double SACstrtod(string *remain, string input)
{
  double res;
  char **rem;
  
  res=strtod(input, rem);
  
  *remain=(string)RT_MALLOC(strlen(*rem)+1);
  strcpy(*remain, *rem);
  
  return(res);
}


/*****************************************************************/

double SACtod(string input)
{
  return(strtod(input, NULL));
}


/*****************************************************************/
