/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

void strovwt(ND_KS_DEC_OUT_RC(string, new),
             ND_KS_DEC_IN_RC(string, old),
             int pos, string insert)
{
  ND_DECL_RC(string, new)
  int len_old=strlen(old);
  int len_insert=strlen(insert);
  int len_insert_pos=len_insert+pos;
  char store;
  
  RANGECHECK(pos, 0, strlen(old), old);
  
  if (len_insert_pos<=len_old)
  {
	 store=old[len_insert_pos];

	 if (ND_A_RC(old)==1)
	 {
		new=old;
		strcpy(new+pos, insert);
		ND_A_RCP(new)=ND_A_RCP(old);
	 }
	 else
	 {
		STRDUP(new, old);
		strcpy(new+pos, insert);
		ND_ALLOC_RC(new);
		ND_SET_RC(new, 1);
		ND_DEC_RC_FREE_ARRAY(old, 1);
	 }

	 new[len_insert_pos]=store;  
  }
  else
  {
	 new=(string)MALLOC(len_insert_pos+1);
	 strncpy(new, old, pos);
    new[pos]=0;
    
	 strcat(new, insert);
	 ND_ALLOC_RC(new);
	 ND_SET_RC(new, 1);
	 ND_DEC_RC_FREE_ARRAY(old, 1);
  }

  ND_KS_RET_OUT_RC(new);
}



/*****************************************************************/
