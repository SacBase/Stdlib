#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

#define subs_nt (subs, T_OLD((SCL, (HID, (NUQ,)))))

void SAC_StringArray_free( array *arr)
{
  int i;
  SAC_ND_DECL__DESC( subs_nt, );
  char * SAC_ND_A_FIELD( subs_nt);

  for( i=0; i<arr->size; i++) {
    SAC_ND_A_DESC( subs_nt) = arr->descs[i];
    SAC_ND_A_FIELD( subs_nt) = arr->data[i];
    /*SAC_ND_DEC_RC_FREE( subs_nt, 1 , free );*/
  }
  /*free( arr->shp);*/
  /*free( arr->data);*/
  /*free( arr->descs);*/
  /*free( arr);*/
}

