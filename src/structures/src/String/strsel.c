/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

char strsel(string s, int pos)
{
  RANGECHECK(pos, 0, strlen(s)-1, s);
  
  return(s[pos]);
}


/*****************************************************************/


