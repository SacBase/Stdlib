/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void cons( ND_KS_DEC_OUT_RC(list *, res), int elem, ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now: 
 * - list **res__p;
 * -  int **__res_rc__p;
 * -  int elem;
 * - list *elems;
 * -  int *__elems_rc;
 */

  list * res;

  res = (list *)malloc(sizeof(list));
  res->rc = 1;
  res->elem = elem;
  res->rest = elems;

#if TRACE
    fprintf( stderr, "creating CONS at (%p)\n", res);
    fprintf( stderr, "       [ %d   .   (%p)]\n", elem, elems);
#endif


  *res__p = res;
  *__res_rc__p = &res->rc;
}

