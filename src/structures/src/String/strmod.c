/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void strmod(ND_KS_DEC_OUT_RC(string, new), 
				ND_KS_DEC_IN_RC(string, old),
				int pos, char c)
{
  ND_DECL_RC(string, new);

  RANGECHECK(pos, 0, strlen(old)-1, old);
  
  if (ND_A_RC(old)==1)
  {
	 new=old;
	 new[pos]=c;

	 ND_A_RCP(new)=ND_A_RCP(old);
  }
  else
  {
	 STRDUP(new, old);
	 new[pos]=c;
	 
	 ND_ALLOC_RC(new);
	 ND_SET_RC(new, 1);

	 ND_DEC_RC(old, 1);
  }
  
  ND_KS_RET_OUT_RC(new);
}
  
	 

/*****************************************************************/

