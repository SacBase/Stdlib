/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void to_string(SAC_ND_KS_DEC_OUT_RC(string, str),
               SAC_ND_KS_DEC_IN_RC(char*, ar),
               int length)
{
  SAC_ND_DECL_RC(string, str);
  
  if ((SAC_ND_A_RC(ar)==1) && (ar[length-1]==0))
  {
	 str=ar;
	 SAC_ND_A_RCP(str)=SAC_ND_A_RCP(ar);
  }
  else
  {
	 str=(string)SAC_MALLOC(length+1);
    strncpy(str, SAC_ND_A_FIELD(ar), length);
	 str[length]=0;
	 
	 SAC_ND_ALLOC_RC(str);
	 SAC_ND_SET_RC(str, 1);

	 SAC_ND_DEC_RC_FREE_ARRAY(ar, 1);
  }

  SAC_ND_KS_RET_OUT_RC(str);
}
  

/*****************************************************************/
