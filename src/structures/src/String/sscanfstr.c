/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string sscanf_str(string s, string format)
{
  string new;
  
  new=(string)SAC_MALLOC(strlen(s)+1);
  
  new[0]=0;
  
  sscanf(s, format, new);

  return(new);
}
 

  
  

/*****************************************************************/


