/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#define res_nt   (res,   (SCL, (HID, (NUQ,))))
#define elems_nt (elems, (SCL, (HID, (NUQ,))))

void drop( SAC_ND_PARAM_out( res_nt, list *),
           int n,
           SAC_ND_PARAM_in( elems_nt, list *))
{
  SAC_ND_DECL__DESC( res_nt, )
  SAC_ND_DECL__DATA( res_nt, list *, )

  if (n < 0) {
    SAC_RuntimeError( "negative first arg of drop\n");
  }

  SAC_ND_A_DESC( res_nt) = SAC_ND_A_DESC( elems_nt);
  SAC_ND_A_FIELD( res_nt) = SAC_ND_A_FIELD( elems_nt);

  while (n > 0) {
    if (res->rest == NULL) {
      SAC_RuntimeError( "first arg of drop %d larger than length of list\n", n);
    }
    res=res->rest;
    n--;
  }
  (DESC_RC( res->desc))++;

  if (--(DESC_RC( elems->desc)) == 0) {
    free_list( elems);
  }

  SAC_ND_A_DESC( res_nt) = res->desc;
  SAC_ND_RET_out( res_nt, res_nt)
}

#undef res_nt
#undef elems_nt
