/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string SACbtos(bool n)
{
  char *res;
  
  res=(char*)SAC_MALLOC(8);
  
  if (n)
  {
    strcpy(res, "true");
  }
  else
  {
    strcpy(res, "false");
  }
    
  return(res);
}


/*****************************************************************/


