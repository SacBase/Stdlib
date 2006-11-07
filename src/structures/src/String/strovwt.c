/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

#define new_nt (new, (SCL, (HID, (NUQ,))))
#define old_nt (old, (SCL, (HID, (NUQ,))))

void strovwt( SAC_ND_PARAM_out( new_nt, string),
              SAC_ND_PARAM_in( old_nt, string),
              int pos, string insert)
{
  SAC_ND_DECL__DESC( new_nt, )
  SAC_ND_DECL__DATA( new_nt, string, )
  int len_old = strlen( SAC_ND_A_FIELD( old_nt));
  int len_insert = strlen( insert);
  int len_insert_pos = len_insert+pos;
  char store;

  RANGECHECK( (size_t)pos, 0, strlen( SAC_ND_A_FIELD( old_nt)),
              SAC_ND_A_FIELD( old_nt));
  
  if (len_insert_pos <= len_old) {
    store = SAC_ND_A_FIELD( old_nt)[len_insert_pos];

    if (SAC_ND_A_RC( old_nt) == 1) {
      SAC_ND_A_DESC( new_nt) = SAC_ND_A_DESC( old_nt);
      SAC_ND_A_FIELD( new_nt) = SAC_ND_A_FIELD( old_nt);
      strcpy( SAC_ND_A_FIELD( new_nt) + pos, insert);
    }
    else {
      SAC_ND_ALLOC__DESC( new_nt, 0)
      SAC_ND_SET__RC( new_nt, 1)
      STRDUP( SAC_ND_A_FIELD( new_nt), SAC_ND_A_FIELD( old_nt));
      strcpy( SAC_ND_A_FIELD( new_nt) + pos, insert);

      SAC_ND_DEC_RC_FREE( old_nt, 1, SAC_FREE)
    }
    SAC_ND_A_FIELD( new_nt)[len_insert_pos] = store;
  }
  else {
    SAC_ND_ALLOC__DESC( new_nt, 0)
    SAC_ND_SET__RC( new_nt, 1)
    SAC_ND_A_FIELD( new_nt) = (string) SAC_MALLOC( len_insert_pos + 1);
    strncpy( SAC_ND_A_FIELD( new_nt), SAC_ND_A_FIELD( old_nt), pos);
    SAC_ND_A_FIELD( new_nt)[pos] = '\0';

    strcat( SAC_ND_A_FIELD( new_nt), insert);

    SAC_ND_DEC_RC_FREE( old_nt, 1, SAC_FREE)
  }

  SAC_ND_RET_out( new_nt, new_nt)
}

#undef new_nt
#undef old_nt

/*****************************************************************/
