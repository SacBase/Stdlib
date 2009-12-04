#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

int SAC_StringArray_index2offset( int dim, int *idx, int *shp)
{
  int i, offset;

  if( dim == 0) {
    offset = 0;
  }
  else {
    offset = idx[0];
    for( i=1; i< dim; i++) {
      offset = (offset * shp[i]) + idx[i];
    }
  }
  return( offset);
}

