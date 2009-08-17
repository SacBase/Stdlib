#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

#define strout_nt (strout, T_OLD((SCL, (HID, (NUQ,)))))
#define str_nt    (str,    T_OLD((SCL, (HID, (NUQ,)))))
#define idx_nt    (idx,    T_OLD((AKD, (NHD, (NUQ,)))))
#define arr_nt    (arr,    T_OLD((SCL, (HID, (NUQ,)))))

void SAC_StringArray_sel(  SAC_ND_PARAM_out( strout_nt, char *),
                              SAC_ND_PARAM_in( idx_nt, int ),
                              SAC_ND_PARAM_in( arr_nt, array *))
{
  int offset;
  SAC_ND_DECL__DESC( str_nt, );
  char *SAC_ND_A_FIELD( str_nt );

  offset = SAC_StringArray_index2offset( arr->dim,
                                         SAC_ND_A_FIELD(idx_nt),
                                         arr->shp);

  SAC_ND_A_FIELD( str_nt) = arr->data[offset];
  SAC_ND_A_DESC( str_nt) = arr->descs[offset];
  SAC_ND_INC_RC( str_nt, 1);

  SAC_ND_DEC_RC_FREE( idx_nt, 1 , );
  SAC_ND_DEC_RC_FREE( arr_nt, 1 , SAC_StringArray_free );

  SAC_ND_RET_out( strout_nt , str_nt )
}

