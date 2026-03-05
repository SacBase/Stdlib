#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

SACarg *SAC_StringArray_sel(SACarg *idx, array *labs)
{
    sac_int offset = SAC_StringArray_index2offset(idx, labs->shp);

    return SACARGduplicateSaCArray(labs->elems[offset]);
}
