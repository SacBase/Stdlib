/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void cons( SAC_ND_PARAM_out_rc( list *, res),
           int elem,
           SAC_ND_PARAM_in_rc( list *, elems))
{
  /*
   * we do have now: 
   * - list **res__p;
   * -  int **res__rc__p;
   * -  int elem;
   * - list *elems;
   * -  int *elems__rc;
   */

  list *res;

  res = (list *)SAC_MALLOC(sizeof(list));
  res->rc = 1;
  res->elem = elem;
  res->rest = elems;

#if TRACE
    fprintf( stderr, "creating CONS at (%p)\n", res);
    fprintf( stderr, "       [ %d   .   (%p)]\n", elem, elems);
#endif

  *res__p = res;
  *res__rc__p = &res->rc;
}
