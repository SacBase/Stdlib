/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string strins(string old, int pos, string insert)
{
  string new;
  
  RANGECHECK(pos, 0, strlen(old), old);
  
  new=(string)MALLOC(strlen(old)+strlen(insert)+1);
  
  strncpy(new, old, pos);
  new[pos]=0;
  
  strcat(new, insert);
  strcat(new, old+pos);
  
  return(new);
}


/*****************************************************************/
