/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#define res_nt   (res,   T_OLD((SCL, (HID, (NUQ,)))))
#define elems_nt (elems, T_OLD((SCL, (HID, (NUQ,)))))

void SAC_List_cons( SAC_ND_PARAM_out( res_nt, list *),
           int elem,
           SAC_ND_PARAM_in( elems_nt, list *))
{
  SAC_ND_DECL__DESC( res_nt, )
  SAC_ND_DECL__DATA( res_nt, list *, )

  res = (list *) SAC_MALLOC( sizeof( list));
  res->elem = elem;
  res->rest = elems;
  SAC_ND_ALLOC__DESC( res_nt, 0)
  SAC_ND_SET__RC( res_nt, 1)
  res->desc = SAC_ND_A_DESC( res_nt);

#if TRACE
  fprintf( stderr, "creating CONS at (%p)\n", res);
  fprintf( stderr, "       [ %d   .   (%p)]\n", elem, elems);
#endif

  SAC_ND_RET_out( res_nt, res_nt)
}

#undef res_nt
#undef elemsA_nt
#undef elemsB_nt
#undef new_nt
