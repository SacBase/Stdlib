#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

int SAC_StringArray_index2offset( int dim, int *idx, int *shp)
{
  int i, offset, size;

  offset = 0;
  size = 1;
  for( i=dim - 1; i >= 0; i--) {
    offset += size * idx[i];
    size *= shp[i];
  }

  return( offset);
}

