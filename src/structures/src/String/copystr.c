/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string copy_string(string s)
{
  string new;
  
  STRDUP(new, s);
  
  return(new);
}


/*****************************************************************/


