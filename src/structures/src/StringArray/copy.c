#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

array *SAC_StringArray_copy(array *arr)
{
    array *res = SAC_StringArray_alloc(arr->dim, arr->size);

    for (sac_int l = 0; l < arr->dim; l++) {
        (res->shp)[l] = (arr->shp)[l];
    }

    for (sac_int i = 0; i < arr->size; i++) {
        (res->elems)[l] = SACARGduplicateSaCArray((arr->elems)[l]);
    }

    return res;
}

