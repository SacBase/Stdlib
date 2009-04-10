/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

#define new_nt (new, T_OLD((SCL, (HID, (NUQ,)))))
#define old_nt (old, T_OLD((SCL, (HID, (NUQ,)))))

void strmod( SAC_ND_PARAM_out( new_nt, string),
             SAC_ND_PARAM_in( old_nt, string),
             int pos, char c)
{
  SAC_ND_DECL__DATA( new_nt, string, )
  SAC_ND_DECL__DESC( new_nt, )

  RANGECHECK( (size_t)pos, 0, strlen( SAC_ND_A_FIELD( old_nt)) - 1,
              SAC_ND_A_FIELD( old_nt));

  if (SAC_ND_A_RC( old_nt) == 1) {
    SAC_ND_A_DESC( new_nt) = SAC_ND_A_DESC( old_nt);
    SAC_ND_A_FIELD( new_nt) = SAC_ND_A_FIELD( old_nt);
  }
  else {
    SAC_ND_ALLOC__DESC( new_nt, 0)
    SAC_ND_SET__RC( new_nt, 1)
    STRDUP( SAC_ND_A_FIELD( new_nt), SAC_ND_A_FIELD( old_nt));

    SAC_ND_DEC_RC_FREE( old_nt, 1, SAC_FREE)
  }
  SAC_ND_A_FIELD( new_nt)[pos] = c;

  SAC_ND_RET_out( new_nt, new_nt)
}

#undef new_nt
#undef old_nt

/*****************************************************************/
