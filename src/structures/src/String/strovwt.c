/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

#ifdef TAGGED_ARRAYS

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

  RANGECHECK( pos, 0, strlen( SAC_ND_A_FIELD( old_nt)),
              SAC_ND_A_FIELD( old_nt));
  
  if (len_insert_pos <= len_old) {
    store = SAC_ND_A_FIELD( old_nt)[len_insert_pos];

    if (SAC_ND_A_RC( old_nt) == 1) {
      SAC_ND_A_DESC( new_nt) = SAC_ND_A_DESC( old_nt);
      SAC_ND_A_FIELD( new_nt) = SAC_ND_A_FIELD( old_nt);
      strcpy( SAC_ND_A_FIELD( new_nt) + pos, insert);
    }
    else {
      SAC_ND_ALLOC__DESC( new_nt)
      SAC_ND_SET__RC( new_nt, 1)
      STRDUP( SAC_ND_A_FIELD( new_nt), SAC_ND_A_FIELD( old_nt));
      strcpy( SAC_ND_A_FIELD( new_nt) + pos, insert);

      SAC_ND_DEC_RC( old_nt, 1)
    }
    SAC_ND_A_FIELD( new_nt)[len_insert_pos] = store;
  }
  else {
    SAC_ND_ALLOC__DESC( new_nt)
    SAC_ND_SET__RC( new_nt, 1)
    SAC_ND_A_FIELD( new_nt) = (string) SAC_MALLOC( len_insert_pos + 1);
    strncpy( SAC_ND_A_FIELD( new_nt), SAC_ND_A_FIELD( old_nt), pos);
    SAC_ND_A_FIELD( new_nt)[pos] = '\0';

    strcat( SAC_ND_A_FIELD( new_nt), insert);

    SAC_ND_DEC_RC_FREE( old_nt, 1, SAC_FREE)
  }

  SAC_ND_RET_out( new_nt, new_nt)
}

#else

void strovwt( SAC_ND_PARAM_out_rc( string, new),
              SAC_ND_PARAM_in_rc( string, old),
              int pos, string insert)
{
  SAC_ND_DECL_RC(string, new)
  int len_old=strlen(old);
  int len_insert=strlen(insert);
  int len_insert_pos=len_insert+pos;
  char store;
  
  RANGECHECK(pos, 0, strlen(old), old);
  
  if (len_insert_pos<=len_old) {
    store=old[len_insert_pos];

    if (SAC_ND_A_RC(old)==1) {
      new=old;
      strcpy(new+pos, insert);
      SAC_ND_A_RCP(new)=SAC_ND_A_RCP(old);
    }
    else {
      STRDUP(new, old);
      strcpy(new+pos, insert);
      SAC_ND_ALLOC_RC(new);
      SAC_ND_SET_RC(new, 1);
      SAC_ND_DEC_RC_FREE_ARRAY(old, 1);
    }
    new[len_insert_pos]=store;  
  }
  else {
    new=(string)SAC_MALLOC(len_insert_pos+1);
    strncpy(new, old, pos);
    new[pos]=0;
    
    strcat(new, insert);
    SAC_ND_ALLOC_RC(new);
    SAC_ND_SET_RC(new, 1);
    SAC_ND_DEC_RC_FREE_ARRAY(old, 1);
  }

  SAC_ND_RET_out_rc( new, new);
}

#endif

/*****************************************************************/
