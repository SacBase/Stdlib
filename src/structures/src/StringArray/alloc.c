#include <stdio.h>
#include <stdlib.h>

#include <sacinterface.h>
#include "StringArray.h"

/* Or should this return SACarg? */
array *SAC_StringArray_alloc(sac_int dim, sac_int size)
{
  array *res;

  res = (array *)malloc(sizeof(array));
  res->dim   = dim;
  res->size  = size;
  res->shp   = (sac_int *)malloc(res->dim * sizeof(sac_int));
  res->elems = (SACarg **)malloc(res->size * sizeof(SACarg *));
  
  return res;
}
