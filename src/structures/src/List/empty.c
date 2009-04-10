/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#define elems_nt (elems, T_OLD((SCL, (HID, (NUQ,)))))

int SAC_List_empty( SAC_ND_PARAM_in( elems_nt, list *))
{
  int res;

  res = (elems->rest == NULL);

  if (--(DESC_RC( elems->desc)) == 0) {
    SAC_List_free_list( elems);
  }

  return( res);
}

#undef elems_nt
