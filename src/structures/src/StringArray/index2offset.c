#include <stdio.h>
#include <stdlib.h>

#include "StringArray.h"

sac_int SAC_StringArray_index2offset(SACarg *idx_in, sac_int *shp)
{
    sac_int dim = SACARGgetDim(idx_in);

    sac_int *idx = (sac_int *)SACARGgetSharedData (SACTYPE__MAIN__int, idx_in);
  
    sac_int offset = 0;
    sac_int size = 1;
    for (sac_int i = dim - 1; i >= 0; i--) {
        offset += size * idx[i];
        size *= shp[i];
    }
  
    return offset;
}
