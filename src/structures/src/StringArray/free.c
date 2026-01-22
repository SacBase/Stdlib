#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

array *SAC_StringArray_free(array *arr)
{
    for (sac_int i = 0; i < arr->size; i++) {
        SACARGdeleteSacArray(&(arr->elems)[i]);
    }
    free(arr->shp);
    free(arr->elems);
    free(arr);
    return NULL;
}

