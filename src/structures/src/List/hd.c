/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#define elems_nt (elems, (SCL, (HID, (NUQ,))))

int hd( SAC_ND_PARAM_in( elems_nt, list *))
{
  int res;

  if (elems->rest == NULL) {
    SAC_RuntimeError( "hd applied to NIL\n");
  }
  res = elems->elem;

  if (--(DESC_RC( elems->desc)) == 0) {
    free_list( elems);
  }

  return( res);
}

#undef elems_nt
