/*
 *  Implementation of SAC standard module List
 */


#include <stdio.h>
#include <stdlib.h>

#include "sac.h"


#define TRACE 0


typedef struct LIST {
  int                    elem;
  struct LIST            *rest;
  SAC_array_descriptor_t desc;
} list;


extern void free_list( list *elems);
