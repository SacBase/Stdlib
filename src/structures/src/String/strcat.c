/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string SACstrcat(string first, string second)
{
  string new;
  
  new=(string)RT_MALLOC(strlen(first)+strlen(second)+1);
  
  strcpy(new, first);
  strcat(new, second);
  
  return(new);
}
  


/*****************************************************************/
