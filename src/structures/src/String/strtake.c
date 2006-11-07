/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

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

    SAC_ND_DEC_RC_FREE( old_nt, 1, SAC_FREE)
  }
  SAC_ND_A_FIELD( new_nt)[n] = '\0';

  SAC_ND_RET_out( new_nt, new_nt)
}

#undef new_nt
#undef old_nt

/*****************************************************************/
