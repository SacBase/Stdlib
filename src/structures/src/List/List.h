/*
 *  Implementation of SAC standard module List
 */


#include <stdio.h>
#include <stdlib.h>

#include "sac.h"


#define TRACE 0


#ifdef TAGGED_ARRAYS
     
typedef struct LIST {
  int                  elem;
  struct LIST          *rest;
  SAC_array_descriptor *desc;
} list;

#else

/*
 * CAUTION:
 * For the time being in SAC reference counter and data vector must be
 * allocated/deallocated separately. Therefore, the field 'rc' must be a
 * POINTER to the reference counter and not the reference counter itself.
 * (i.e. the type is int* not int)
 */
typedef struct LIST {
  int         elem;
  struct LIST *rest;
  int         *rc;
} list;

#endif


extern void free_list( list *elems);
