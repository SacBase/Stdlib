/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void strovwt(SAC_ND_KS_DEC_OUT_RC(string, new),
             SAC_ND_KS_DEC_IN_RC(string, old),
             int pos, string insert)
{
  SAC_ND_DECL_RC(string, new)
  int len_old=strlen(old);
  int len_insert=strlen(insert);
  int len_insert_pos=len_insert+pos;
  char store;
  
  RANGECHECK(pos, 0, strlen(old), old);
  
  if (len_insert_pos<=len_old)
  {
	 store=old[len_insert_pos];

	 if (SAC_ND_A_RC(old)==1)
	 {
		new=old;
		strcpy(new+pos, insert);
		SAC_ND_A_RCP(new)=SAC_ND_A_RCP(old);
	 }
	 else
	 {
		STRDUP(new, old);
		strcpy(new+pos, insert);
		SAC_ND_ALLOC_RC(new);
		SAC_ND_SET_RC(new, 1);
		SAC_ND_DEC_RC_FREE_ARRAY(old, 1);
	 }

	 new[len_insert_pos]=store;  
  }
  else
  {
	 new=(string)SAC_MALLOC(len_insert_pos+1);
	 strncpy(new, old, pos);
    new[pos]=0;
    
	 strcat(new, insert);
	 SAC_ND_ALLOC_RC(new);
	 SAC_ND_SET_RC(new, 1);
	 SAC_ND_DEC_RC_FREE_ARRAY(old, 1);
  }

  SAC_ND_KS_RET_OUT_RC( new, new);
}



/*****************************************************************/


