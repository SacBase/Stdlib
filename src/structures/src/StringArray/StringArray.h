/*
 *  Implementation of SAC standard module StringArray
 */


#include <stdio.h>
#include <stdlib.h>

#include <sacinterface.h>

/* Keep consistent with src/String/StringC.h */
typedef char* string;

typedef struct ARRAY {
  sac_int                dim;
  sac_int                size;
  sac_int                *shp;
  SACarg                 **elems;
} array;

extern array *SAC_StringArray_alloc(sac_int dim, sac_int size);

extern sac_int dim(array *s);

/* This is just a helper function */
extern sac_int SAC_StringArray_index2offset(SACarg *idx, sac_int *shp);

extern array *SAC_StringArray_free(array *arr);
extern array *SAC_StringArray_copy(array *arr);

extern SACarg *shape(array *s);

extern array *SAC_StringArray_genarray(SACarg *shp, SACarg *s);

extern SACarg *SAC_StringArray_sel(SACarg *idx, array *labs);

extern void SAC_StringArray_modarray(array *labs, SACarg *idx, SACarg *str);
