/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#define res_nt (res, (SCL, (HID, (NUQ,))))

void nil( SAC_ND_PARAM_out( res_nt, list *))
{
  SAC_ND_DECL__DESC( res_nt, )
  SAC_ND_DECL__DATA( res_nt, list *, )

  res = (list *) SAC_MALLOC( sizeof( list));
  res->rest = NULL;
  SAC_ND_ALLOC__DESC( res_nt, 0)
  SAC_ND_SET__RC( res_nt, 1)
  res->desc = SAC_ND_A_DESC( res_nt);

#if TRACE
  fprintf( stderr, "creating NIL at (%p)\n", res);
#endif

  SAC_ND_RET_out( res_nt, res_nt)
}

#undef res_nt
