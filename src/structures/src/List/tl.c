/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void tl( SAC_ND_KS_DEC_OUT_RC(list *, res), SAC_ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now:
 * - list **res__p;
 * -  int **__res_rc__p;
 * - list *elems;
 * -  int *__elems_rc;
 */
  list * res;

  if( elems->rest == NULL)
    __SAC__Runtime_Error( "tl applied to NIL\n");
  res = elems->rest;

  res->rc++;

  if(--elems->rc == 0)
    free_list( elems);

  *res__p = res;
  *__res_rc__p = &res->rc;
}


