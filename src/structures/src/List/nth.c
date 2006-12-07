/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#define elems_nt (elems, (SCL, (HID, (NUQ,))))

int SAC_List_nth( int n, SAC_ND_PARAM_in( elems_nt, list *))
{
  list *ptr;
  int res;

  if (n < 0) {
    SAC_RuntimeError( "negative first arg of nth\n");
  }

  ptr = elems;
  while (n > 0) {
    ptr = ptr->rest;
    if (ptr->rest == NULL) {
      SAC_RuntimeError( "first arg of nth %d larger than length of list\n", n);
    }
    n--;
  }
  res = ptr->elem;

  if (--(DESC_RC( elems->desc)) == 0) {
    SAC_List_free_list( elems);
  }

  return( res);
}

#undef elems_nt
