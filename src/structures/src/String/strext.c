/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string strext(string old, int first, int len)
{
  string new;
  
  RANGECHECK(first, 0, strlen(old)-1, old);
  
  if (len<=0)
  {
	 new=(string)SAC_MALLOC(1);
	 new[0]=0;
  }
  else
  {
	 new=(string)SAC_MALLOC(len+1);
	 strncpy(new, old+first, len);
    
    if (first+len<=strlen(old))
    {
      new[len]=0;
    }
    else
    {
      new[strlen(old)-first]=0;
    }
  }
  
  return(new);
}


/*****************************************************************/


