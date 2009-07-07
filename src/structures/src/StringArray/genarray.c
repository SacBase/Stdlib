#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

#define resout_nt (resout, T_OLD((SCL, (HID, (NUQ,)))))
#define res_nt    (res, T_OLD((SCL, (HID, (NUQ,)))))
#define shp_nt    (shp, T_OLD((AKD, (HID, (NUQ,)))))
#define s_nt      (s,   T_OLD((SCL, (HID, (NUQ,)))))

void SAC_StringArray_genarray( SAC_ND_PARAM_out( resout_nt, array *),
                               SAC_ND_PARAM_in( shp_nt, int ),
                               SAC_ND_PARAM_in( s_nt, char *))
{
  SAC_ND_DECL__DESC( res_nt, );
  array *SAC_ND_A_FIELD( res_nt );
  int SAC_ND_A_MIRROR_SIZE( shp_nt) = SAC_ND_A_DESC_SIZE( shp_nt );
  int dim, size;
  int i;

  SAC_ND_ALLOC__DESC( res_nt, 0);
  SAC_ND_SET__RC( res_nt, 1);


  dim = SAC_ND_A_DESC_SIZE( shp_nt );
  size = 1;
  for( i=0; i < dim; i++) {
    size *= SAC_ND_READ( shp_nt, i);
  }

  res = SAC_StringArray_alloc( dim, size);

  for( i=0; i < dim; i++) {
    res->shp[i] = SAC_ND_READ( shp_nt, i);
  }

  for( i=0; i < rav_len ; i++) {
    res->data[i] = SAC_ND_A_FIELD( s_nt );
    res->descs[i] = SAC_ND_A_DESC( s_nt );
    SAC_ND_INC_RC( s_nt, 1);
  }

  SAC_ND_DEC_RC_FREE( s_nt, 1 , free );
  SAC_ND_DEC_RC_FREE( shp_nt, 1 , );

  SAC_ND_RET_out( resout_nt , res_nt )

}


