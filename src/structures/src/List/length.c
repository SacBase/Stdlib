/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#define elems_nt (elems, (SCL, (HID, (NUQ,))))

int length( SAC_ND_PARAM_in( elems_nt, list *))
{
  list *ptr = elems;
  int res = 0;

  while (ptr->rest != NULL) {
    ptr = ptr->rest;
    res++;
  }
  if (--(DESC_RC( elems->desc)) == 0) {
    free_list( elems);
  }

  return( res);
}

#undef elems_nt
