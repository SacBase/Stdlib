#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

void SAC_StringArray_modarray(array *labs, SACarg *idx, SACarg *str)
{
    sac_int offset = SAC_StringArray_index2offset(idx, labs->shp);
    SACARGdeleteSacArray(&(labs->elems[offset]));
    labs->elems[offset] = SACARGduplicateSaCArray(str);
}
