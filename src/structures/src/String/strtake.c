/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void strtake(ND_KS_DEC_OUT_RC(string, new),
				 ND_KS_DEC_IN_RC(string, old),
				 int n)
{
  ND_DECL_RC(string, new);
  
  RANGECHECK(n, 0, strlen(old), old);
  
  if (ND_A_RC(old)==1)
  {
	 new=old;
	 new[n]=0;
	 ND_A_RCP(new)=ND_A_RCP(old);
  }
  else
  {
	 new=(string)MALLOC(n+1);
	 strncpy(new, old, n);
    new[n]=0;
    
	 ND_ALLOC_RC(new);
	 ND_SET_RC(new, 1);
  }
  
  ND_KS_RET_OUT_RC(new);
}



/*****************************************************************/
