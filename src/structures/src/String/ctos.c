/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string SACctos(double *n)
{
  char *res;
  
  res=(char*)RT_MALLOC(120);
  
  sprintf(res, "(%g,%g)", n[0], n[1]);
  
  return(res);
}


/*****************************************************************/
