/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

#ifdef TAGGED_ARRAYS

#define new_nt (new, (SCL, (HID, (NUQ,))))
#define old_nt (old, (SCL, (HID, (NUQ,))))

void strmod( SAC_ND_PARAM_out( new_nt, string),
             SAC_ND_PARAM_in( old_nt, string),
             int pos, char c)
{
  SAC_ND_DECL__DATA( new_nt, string, )
  SAC_ND_DECL__DESC( new_nt, )

  RANGECHECK( pos, 0, strlen( SAC_ND_A_FIELD( old_nt)) - 1,
              SAC_ND_A_FIELD( old_nt));

  if (SAC_ND_A_RC( old_nt) == 1) {
    SAC_ND_A_DESC( new_nt) = SAC_ND_A_DESC( old_nt);
    SAC_ND_A_FIELD( new_nt) = SAC_ND_A_FIELD( old_nt);
  }
  else {
    SAC_ND_ALLOC__DESC( new_nt)
    SAC_ND_SET__RC( new_nt, 1)
    STRDUP( SAC_ND_A_FIELD( new_nt), SAC_ND_A_FIELD( old_nt));

    SAC_ND_DEC_RC( old_nt, 1)
  }
  SAC_ND_A_FIELD( new_nt)[pos] = c;

  SAC_ND_RET_out( new_nt, new_nt)
}

#else

void strmod( SAC_ND_PARAM_out_rc( string, new),
             SAC_ND_PARAM_in_rc( string, old),
             int pos, char c)
{
  SAC_ND_DECL_RC(string, new);

  RANGECHECK(pos, 0, strlen(old)-1, old);
  
  if (SAC_ND_A_RC(old)==1) {
    new=old;
    new[pos]=c;

    SAC_ND_A_RCP(new)=SAC_ND_A_RCP(old);
  }
  else {
    STRDUP(new, old);
    new[pos]=c;
	 
    SAC_ND_ALLOC_RC(new);
    SAC_ND_SET_RC(new, 1);

    SAC_ND_DEC_RC(old, 1);
  }
  
  SAC_ND_RET_out_rc( new, new);
}

#endif

/*****************************************************************/
