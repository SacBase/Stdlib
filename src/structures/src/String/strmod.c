/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void strmod(SAC_ND_KS_DEC_OUT_RC(string, new), 
				SAC_ND_KS_DEC_IN_RC(string, old),
				int pos, char c)
{
  SAC_ND_DECL_RC(string, new);

  RANGECHECK(pos, 0, strlen(old)-1, old);
  
  if (SAC_ND_A_RC(old)==1)
  {
	 new=old;
	 new[pos]=c;

	 SAC_ND_A_RCP(new)=SAC_ND_A_RCP(old);
  }
  else
  {
	 STRDUP(new, old);
	 new[pos]=c;
	 
	 SAC_ND_ALLOC_RC(new);
	 SAC_ND_SET_RC(new, 1);

	 SAC_ND_DEC_RC(old, 1);
  }
  
  SAC_ND_KS_RET_OUT_RC(new);
}
  
	 

/*****************************************************************/

