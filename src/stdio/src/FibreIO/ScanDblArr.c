/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"



#define array_nt (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define ret_nt   (ret,   T_OLD((AUD, (NHD, (NUQ, )))))

void FibreScanDoubleArray( SAC_ND_PARAM_out( array_nt, double), FILE *stream)
{
  SAC_ND_DECL__DATA( ret_nt, double, )
  SAC_ND_DECL__DESC( ret_nt, )
  int i;
  start_token = PARSE_DOUBLE_ARRAY;
  yyin = stream;
  FibreScanparse();
  int SAC_ND_A_MIRROR_DIM( ret_nt) = dims;
  SAC_ND_ALLOC__DESC( ret_nt, dims)
  SAC_ND_SET__RC( ret_nt, 1)
  for( i = 0; i < dims; i++) {
    SAC_ND_A_DESC_SHAPE( ret_nt, i) = shape[i];
  }
  SAC_ND_A_DESC_SIZE( ret_nt) = size;
  SAC_ND_A_FIELD( ret_nt) = doublearray;
  SAC_ND_RET_out( array_nt, ret_nt)
}

#undef array_nt
#undef ret_nt

#define array_nt (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define ret_nt   (ret,   T_OLD((AUD, (NHD, (NUQ, )))))

void FibreScanDoubleArrayStr( SAC_ND_PARAM_out( array_nt, double), char *stream)
{
  SAC_ND_DECL__DATA( ret_nt, double, )
  SAC_ND_DECL__DESC( ret_nt, )
  int i;
  start_token = PARSE_DOUBLE_ARRAY;
  yy_scan_string( stream);
  FibreScanparse();
  int SAC_ND_A_MIRROR_DIM( ret_nt) = dims;
  SAC_ND_ALLOC__DESC( ret_nt, dims)
  SAC_ND_SET__RC( ret_nt, 1)
  for( i = 0; i < dims; i++) {
    SAC_ND_A_DESC_SHAPE( ret_nt, i) = shape[i];
  }
  SAC_ND_A_DESC_SIZE( ret_nt) = size;
  SAC_ND_A_FIELD( ret_nt) = doublearray;
  SAC_ND_RET_out( array_nt, ret_nt)
}

#undef array_nt
#undef ret_nt
