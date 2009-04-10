/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"


#define array_nt (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define ret_nt   (ret,   T_OLD((AUD, (NHD, (NUQ, )))))

void FibreScanFloatArray( SAC_ND_PARAM_out( array_nt, float),
                          FILE *stream,
                          int dim, int *shp)
{
  SAC_ND_DECL__DATA( ret_nt, float, )
  SAC_ND_DECL__DESC( ret_nt, )
  int SAC_ND_A_MIRROR_DIM( ret_nt) = dim;
  int i, size;
  
  SAC_ND_ALLOC__DESC( ret_nt, dim)
  SAC_ND_SET__RC( ret_nt, 1)

  start_token = PARSE_FLOAT_ARRAY;
  yyin = stream;
  given_dim = dim;
  given_shp = shp;
  for( i = 0, size = 1; i < dim; i++) {
    size *= shp[i];
    SAC_ND_A_DESC_SHAPE( ret_nt, i) = shp[i];
  }
  SAC_ND_A_DESC_SIZE( ret_nt) = size;
  floatarray = (float *) SAC_MALLOC( size * sizeof( float));
  FibreScanparse();
  SAC_ND_A_FIELD( ret_nt) = floatarray;

  SAC_ND_RET_out( array_nt, ret_nt)
}

#undef array_nt
#undef ret_nt
