/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string SACstrncat(string first, string second, int n)
{
  string new;
  
  new=(string)MALLOC(strlen(first)+n+1);
  
  strcpy(new, first);
  strncat(new, second, n);
  
  return(new);
}
 


/*****************************************************************/
