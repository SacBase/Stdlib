#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

#define subs_nt (subs, T_OLD((SCL, (HID, (NUQ,)))))

array *SAC_StringArray_copy( array *arr)
{
  int i;
  array *res;
  SAC_ND_DECL__DESC( subs_nt, );
  char * SAC_ND_A_FIELD( subs_nt);

  res = SAC_StringArray_alloc( arr->dim, arr->size);
  for( i=0; i<arr->dim; i++) {
     res->shp[i] = arr->shp[i];
  }
  for( i=0; i<arr->size; i++) {
    SAC_ND_A_DESC( subs_nt) = arr->descs[i];
    SAC_ND_A_FIELD( subs_nt) = arr->data[i];
    SAC_ND_INC_RC( subs_nt, 1 );
    res->descs[i] = SAC_ND_A_DESC( subs_nt);
    res->data[i] = SAC_ND_A_FIELD( subs_nt);
  }
  return( res);
}

