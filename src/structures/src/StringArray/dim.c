#include "StringArray.h"

#define s_nt      (s,   T_OLD((SCL, (HID, (NUQ,)))))
#define dim_nt    (dim, T_OLD((SCL, (NHD, (NUQ,)))))
#define res_nt    (res, T_OLD((SCL, (NHD, (NUQ,)))))

void SAC_StringArray_dim( SAC_ND_PARAM_out( dim_nt, int),
                          SAC_ND_PARAM_in( s_nt, array *))
{
  SAC_ND_DECL__DESC( res_nt, );
  SAC_ND_DECL__DATA( res_nt, int,); 
  
  SAC_ND_ALLOC__DESC( res_nt, 0);
  SAC_ND_CREATE__SCALAR__DATA( res_nt, s->dim);
  
  SAC_ND_RET_out( dim_nt , res_nt )
}

