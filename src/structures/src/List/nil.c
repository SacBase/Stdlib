/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#ifdef TAGGED_ARRAYS

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

#else  /* TAGGED_ARRAYS */

void nil( SAC_ND_PARAM_out_rc( list *, res))
{
  /*
   * we do have now: 
   * - list **res__p;
   * -  int **res__rc__p;
   */
  list *res;

  res = (list *) SAC_MALLOC( sizeof( list));
  res->rest = NULL;

  res->rc = (int *) SAC_MALLOC( sizeof( int));
  (*res->rc) = 1;

#if TRACE
  fprintf( stderr, "creating NIL at (%p)\n", res);
#endif

  *res__p = res;
  *res__rc__p = res->rc;
}

#endif  /* TAGGED_ARRAYS */
