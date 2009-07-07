/*
 *  Implementation of SAC standard module StringArray
 */


#include <stdio.h>
#include <stdlib.h>

#include "sac.h"


#define TRACE 0

typedef struct ARRAY {
  int                    dim;
  int                    size;
  int                    *shp;
  char                   **data;
  SAC_array_descriptor_t *descs;
} array;

extern array *SAC_StringArray_alloc( int dim, int size);
extern int SAC_StringArray_index2offset( int dim, int *idx, int *shp);

extern void SAC_StringArray_free( array *arr);
extern array *SAC_StringArray_copy( array *arr);

