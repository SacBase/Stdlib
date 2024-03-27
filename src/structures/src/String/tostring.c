/*
 *  implementation of standard module StringC
 */


#include "StringC.h"

/* TODO ar should be PDI */

/*****************************************************************/

#define str_nt (str, T_OLD((SCL, (HID, (NUQ,)))))
#define ar_nt  (ar, T_OLD((AUD, (NHD, (NUQ,)))))

void to_string( SAC_ND_PARAM_out( str_nt, string),
                SAC_ND_PARAM_in( ar_nt, char),
                int length)
{
  SAC_ND_DECL__DESC( str_nt, )
  SAC_ND_DECL__DATA( str_nt, string, )

  SAC_ND_ALLOC__DESC( str_nt, 0)
  SAC_ND_SET__RC( str_nt, 1)
  SAC_ND_A_FIELD( str_nt) = (string) SAC_MALLOC( length + 1);
  strncpy( SAC_ND_A_FIELD( str_nt), SAC_ND_A_FIELD( ar_nt), length);
  SAC_ND_A_FIELD( str_nt)[length] = '\0';

  SAC_ND_RET_out( str_nt, str_nt)
}

#undef str_nt
#undef ar_nt  

/*****************************************************************/
