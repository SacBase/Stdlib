/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void to_string(ND_KS_DEC_OUT_RC(string, str),
               ND_KS_DEC_IN_RC(char*, ar),
               int length)
{
  ND_DECL_RC(string, str);
  
  if ((ND_A_RC(ar)==1) && (ar[length-1]==0))
  {
	 str=ar;
	 ND_A_RCP(str)=ND_A_RCP(ar);
  }
  else
  {
	 str=(string)MALLOC(length+1);
    strncpy(str, ND_A_FIELD(ar), length);
	 str[length]=0;
	 
	 ND_ALLOC_RC(str);
	 ND_SET_RC(str, 1);

	 ND_DEC_RC_FREE_ARRAY(ar, 1);
  }

  ND_KS_RET_OUT_RC(str);
}
  

/*****************************************************************/
