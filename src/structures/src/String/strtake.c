/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

#ifdef TAGGED_ARRAYS

#define new_nt (new, (SCL, (HID, (NUQ,))))
#define old_nt (old, (SCL, (HID, (NUQ,))))

void strtake( SAC_ND_PARAM_out( new_nt, string),
              SAC_ND_PARAM_in( old_nt, string),
              int n)
{
  SAC_ND_DECL__DESC( new_nt, )
  SAC_ND_DECL__DATA( new_nt, string, )

  RANGECHECK( (size_t)n, 0, strlen( SAC_ND_A_FIELD( old_nt)), SAC_ND_A_FIELD( old_nt));
  
  if (SAC_ND_A_RC( old_nt) == 1) {
    SAC_ND_A_DESC( new_nt) = SAC_ND_A_DESC( old_nt);
    SAC_ND_A_FIELD( new_nt) = SAC_ND_A_FIELD( old_nt);
  }
  else {
    SAC_ND_ALLOC__DESC( new_nt, 0)
    SAC_ND_SET__RC( new_nt, 1)
    SAC_ND_A_FIELD( new_nt) = (string) SAC_MALLOC( n + 1);
    strncpy( SAC_ND_A_FIELD( new_nt), SAC_ND_A_FIELD( old_nt), n);

    SAC_ND_DEC_RC( old_nt, 1)
  }
  SAC_ND_A_FIELD( new_nt)[n] = '\0';

  SAC_ND_RET_out( new_nt, new_nt)
}

#else

void strtake( SAC_ND_PARAM_out_rc( string, new),
              SAC_ND_PARAM_in_rc( string, old),
              int n)
{
  SAC_ND_DECL_RC(string, new);
  
  RANGECHECK((size_t)n, 0, strlen(old), old);
  
  if (SAC_ND_A_RC(old)==1) {
    new=old;
    new[n]=0;
    SAC_ND_A_RCP(new)=SAC_ND_A_RCP(old);
  }
  else {
    new=(string)SAC_MALLOC(n+1);
    strncpy(new, old, n);
    new[n]=0;
    SAC_ND_ALLOC_RC(new);
    SAC_ND_SET_RC(new, 1);
  }

  SAC_ND_RET_out_rc( new, new);
}

#endif

/*****************************************************************/
