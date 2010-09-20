/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"

#define array_nt (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define ret_nt   (ret,   T_OLD((AUD, (NHD, (NUQ, )))))

#define SCANARR(type,alias,token)					\
									\
void FibreScan##alias##Array( SAC_ND_PARAM_out( array_nt, type), 	\
FILE *stream)								\
{									\
  SAC_ND_DECL__DATA( ret_nt, type, )					\
  SAC_ND_DECL__DESC( ret_nt, )						\
  int i;								\
  start_token = PARSE_##token##_ARRAY;					\
  doScan( stream);                           \
  int SAC_ND_A_MIRROR_DIM( ret_nt) = dims;				\
  SAC_ND_ALLOC__DESC( ret_nt, dims)					\
  SAC_ND_SET__RC( ret_nt, 1)						\
  for( i = 0; i < dims; i++) {						\
    SAC_ND_A_DESC_SHAPE( ret_nt, i) = shape[i];				\
  }									\
  SAC_ND_A_DESC_SIZE( ret_nt) = size;					\
  SAC_ND_A_FIELD( ret_nt) = type##array;				\
  SAC_ND_RET_out( array_nt, ret_nt)					\
}									\
									\
void FibreScan##alias##ArrayStr( SAC_ND_PARAM_out( array_nt, type), 	\
char *stream)								\
{									\
  SAC_ND_DECL__DATA( ret_nt, type, )					\
  SAC_ND_DECL__DESC( ret_nt, )						\
  int i;								\
  start_token = PARSE_##token##_ARRAY;					\
  yy_scan_string( stream);						\
  FibreScanparse();							\
  int SAC_ND_A_MIRROR_DIM( ret_nt) = dims;				\
  SAC_ND_ALLOC__DESC( ret_nt, dims)					\
  SAC_ND_SET__RC( ret_nt, 1)						\
  for( i = 0; i < dims; i++) {						\
    SAC_ND_A_DESC_SHAPE( ret_nt, i) = shape[i];				\
  }									\
  SAC_ND_A_DESC_SIZE( ret_nt) = size;					\
  SAC_ND_A_FIELD( ret_nt) = type##array;				\
  SAC_ND_RET_out( array_nt, ret_nt)					\
}

SCANARR(byte,Byte,BYTE)
SCANARR(short,Short,SHORT)
SCANARR(long,Long,LONG)
SCANARR(longlong,Longlong,LONGLONG)
SCANARR(ubyte,Ubyte,UBYTE)
SCANARR(ushort,Ushort,USHORT)
SCANARR(uint,Uint,UINT)
SCANARR(ulong,Ulong,ULONG)
SCANARR(ulonglong,Ulonglong,ULONGLONG)

#undef array_nt
#undef ret_nt
