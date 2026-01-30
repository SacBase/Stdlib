#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

array *SAC_StringArray_genarray(SACarg *shp, SACarg *s)
{
    sac_int dim  = SACARGgetDim(shp); 
    sac_int size = 1;
    for (sac_int pos = 0; pos < dim; pos++) {
        size *= SACARGgetShape(shp, pos);
    }
    array *res = SAC_StringArray_alloc(dim, size);
    for (sac_int pos = 0; pos < dim; pos++) {
        res->shp[pos] = SACARGgetShape(shp, pos);
    }

    for (sac_int i = 0; i < size; i++) {
        res->elems[i] = SACARGduplicateSaCArray(s);
    }

    return res;
}


