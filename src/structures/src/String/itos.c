/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string SACitos(int n)
{
  char *res;
  
  res=(char*)MALLOC(40);
  
  sprintf(res, "%d", n);
  
  return(res);
}


/*****************************************************************/
