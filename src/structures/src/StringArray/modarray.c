#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

#define arrout_nt (arrout, T_OLD((SCL, (HID, (NUQ,)))))
#define str_nt    (str,    T_OLD((SCL, (HID, (NUQ,)))))
#define val_nt    (val,    T_OLD((SCL, (HID, (NUQ,)))))
#define idx_nt    (idx,    T_OLD((AKD, (NHD, (NUQ,)))))
#define arr_nt    (arr,    T_OLD((SCL, (HID, (NUQ,)))))

void SAC_StringArray_modarray( SAC_ND_PARAM_out( arrout_nt, array *),
                               SAC_ND_PARAM_in( arr_nt, array *),
                               SAC_ND_PARAM_in( idx_nt, int ),
                               SAC_ND_PARAM_in( val_nt, char * ))
{
  int offset;
  SAC_ND_DECL__DESC( str_nt, );
  char *SAC_ND_A_FIELD( str_nt );

  if( SAC_ND_A_RC( arr_nt) > 1 ) {
    SAC_ND_DEC_RC( arr_nt, 1);
    SAC_ND_A_FIELD( arr_nt) = SAC_StringArray_copy( SAC_ND_A_FIELD( arr_nt));
    SAC_ND_ALLOC__DESC( arr_nt, 0);
    SAC_ND_SET__RC( arr_nt, 1);
  }
  offset = SAC_StringArray_index2offset( arr->dim,
                                         SAC_ND_A_FIELD(idx_nt),
                                         arr->shp);

  SAC_ND_A_FIELD( str_nt) = arr->data[offset];
  SAC_ND_A_DESC( str_nt) = arr->descs[offset];
  SAC_ND_DEC_RC_FREE( str_nt, 1, free);
  arr->data[offset] = SAC_ND_A_FIELD( val_nt);
  arr->descs[offset] = SAC_ND_A_DESC( val_nt);

  SAC_ND_DEC_RC_FREE( idx_nt, 1 , );

  SAC_ND_RET_out( arrout_nt , arr_nt )
}

