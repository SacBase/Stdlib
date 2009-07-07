#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

array *SAC_StringArray_alloc( int dim, int size)
{
  array *res;

  res = (array *)malloc( sizeof( array));
  res->dim = dim;
  res->size = size;
  res->shp = (int*)malloc( res->dim * sizeof( int));
  res->data = (char**) malloc( res->size * sizeof( char *));
  res->descs = (SAC_array_descriptor_t*)
              malloc( res->size * sizeof( SAC_array_descriptor_t *));
  
  return( res);
}

