/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void strtake(SAC_ND_KS_DEC_OUT_RC(string, new),
				 SAC_ND_KS_DEC_IN_RC(string, old),
				 int n)
{
  SAC_ND_DECL_RC(string, new);
  
  RANGECHECK(n, 0, strlen(old), old);
  
  if (SAC_ND_A_RC(old)==1)
  {
	 new=old;
	 new[n]=0;
	 SAC_ND_A_RCP(new)=SAC_ND_A_RCP(old);
  }
  else
  {
	 new=(string)SAC_MALLOC(n+1);
	 strncpy(new, old, n);
    new[n]=0;
    
	 SAC_ND_ALLOC_RC(new);
	 SAC_ND_SET_RC(new, 1);
  }
  
  SAC_ND_KS_RET_OUT_RC(new);
}



/*****************************************************************/
