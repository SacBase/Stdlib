#include "StringArray.h"

SACarg *SAC_StringArray_shape(array *x)
{
    sac_int d    = x->dim;
    sac_int *shp = malloc(d * sizeof(sac_int));

    for (sac_int l = 0; l < d; l++) {
        shp[l] = x->shp[l];
    }

    sac_int n[1] = {d};

    return SACARGcreateFromPointer(SACTYPE__MAIN__int, shp, d, n);
}
