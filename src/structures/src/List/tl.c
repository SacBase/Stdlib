/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void tl( SAC_ND_KS_DEC_OUT_RC(list *, res), SAC_ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now:
 * - list **res__p;
 * -  int **res__rc__p;
 * - list *elems;
 * -  int *elems__rc;
 */
  list * res;

  if( elems->rest == NULL)
    SAC_RuntimeError( "tl applied to NIL\n");
  res = elems->rest;

  res->rc++;

  if(--elems->rc == 0)
    free_list( elems);

  *res__p = res;
  *res__rc__p = &res->rc;
}




