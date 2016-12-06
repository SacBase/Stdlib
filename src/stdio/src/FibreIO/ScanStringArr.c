/*
 *  Implementation of standard module FibreScan
 */


#include "FibreScan.h"
#include "FibreScan.tab.h"

#include "../../../structures/src/StringArray/StringArray.h"

#define resout_nt (resout, T_OLD((SCL, (HID, (NUQ, )))))
#define res_nt    (res,   T_OLD((SCL, (HID, (NUQ, )))))
#define s_nt      (s,   T_OLD((SCL, (HID, (NUQ,)))))


void FibreScanStringArray( SAC_ND_PARAM_out( resout_nt, array *), FILE *stream)
{

  SAC_ND_DECL__DESC( res_nt, );

  array *SAC_ND_A_FIELD( res_nt );
  int size;
  int i;

  SAC_ND_ALLOC__DESC( res_nt, 0);
  SAC_ND_SET__RC( res_nt, 1);

  
  start_token = PARSE_STRING_ARRAY;
  doScan( stream);
  
  size = 1;
  for( i=0; i < dims; i++) {
    size *= shape[i];
  }

  res = SAC_StringArray_alloc( dims, size);

  for( i=0; i < dims; i++) {
    res->shp[i] = shape[i];
  }

  res->data = stringarray;

  for( i=0; i < size ; i++) {
    SAC_ND_DECL__DESC( s_nt, );
    SAC_ND_ALLOC__DESC( s_nt, 0);
    SAC_ND_SET__RC( s_nt, 1);
    res->descs[i] = SAC_ND_A_DESC( s_nt);
  }

  SAC_ND_RET_out( resout_nt, res_nt )
}

#undef resout_nt
#undef res_nt
#undef s_nt

#define resout_nt (resout, T_OLD((SCL, (HID, (NUQ, )))))
#define res_nt    (res,   T_OLD((SCL, (HID, (NUQ, )))))
#define s_nt      (s,   T_OLD((SCL, (HID, (NUQ,)))))

void FibreScanStringArrayStr( SAC_ND_PARAM_out( resout_nt, array *), char *stream)
{

  SAC_ND_DECL__DESC( res_nt, );

  array *SAC_ND_A_FIELD( res_nt );
  int size;
  int i;

  SAC_ND_ALLOC__DESC( res_nt, 0);
  SAC_ND_SET__RC( res_nt, 1);

  
  start_token = PARSE_STRING_ARRAY;
  yy_scan_string( stream);
  FibreScanparse();
  
  size = 1;
  for( i=0; i < dims; i++) {
    size *= shape[i];
  }

  res = SAC_StringArray_alloc( dims, size);

  for( i=0; i < dims; i++) {
    res->shp[i] = shape[i];
  }

  res->data = stringarray;

  for( i=0; i < size ; i++) {
    SAC_ND_DECL__DESC( s_nt, );
    SAC_ND_ALLOC__DESC( s_nt, 0);
    SAC_ND_SET__RC( s_nt, 1);
    res->descs[i] = SAC_ND_A_DESC( s_nt);
  }

  SAC_ND_RET_out( resout_nt, res_nt )
}

#undef resout_nt
#undef res_nt
#undef s_nt

