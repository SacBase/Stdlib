#include "StringArray.h"

#define s_nt      (s,   T_OLD((SCL, (HID, (NUQ,)))))
#define shp_nt    (shp, T_OLD((AKD, (NHD, (NUQ,)))))
#define res_nt    (res, T_OLD((AKD, (NHD, (NUQ,)))))

void SAC_StringArray_shape( SAC_ND_PARAM_out( shp_nt, int),
                            SAC_ND_PARAM_in( s_nt, array *))
{
  int i;
  int SAC_ND_A_MIRROR_DIM( res_nt) = 1;
  SAC_ND_DECL__DESC( res_nt, );
  SAC_ND_DECL__DATA( res_nt, int, ); 

  SAC_ND_ALLOC__DESC( res_nt, 1);

  SAC_ND_A_DESC_SHAPE( res_nt, 0) = 1;

  SAC_ND_A_RC( res_nt) = 1;
  SAC_ND_A_DESC_SIZE( res_nt) = SAC_ND_A_DESC_SHAPE( res_nt, 0);
  SAC_ND_A_FIELD( res_nt) = SAC_MALLOC( s->dim * sizeof( int));
  for( i=0; i<s->dim; i++) {
    SAC_ND_A_FIELD( res_nt)[i] = s->shp[i];
  }

  SAC_ND_RET_out( shp_nt , res_nt )
}

#undef s_nt  
#undef shp_nt
#undef res_nt
