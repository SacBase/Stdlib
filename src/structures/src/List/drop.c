/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void _drop( ND_KS_DEC_OUT_RC(list *, res), int n, ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now:
 * - list **res__p;
 * -  int **__res_rc__p;
 * -  int n;
 * - list *elems;
 * -  int *__elems_rc;
 */
  list * res=elems;

  if( n<0)
    __SAC__Runtime_Error( "negative first arg of drop\n");

  while( n>0) {
    if( res->rest == NULL)
      __SAC__Runtime_Error( "first arg of drop %d larger than length of list\n", n);
    res=res->rest;
    n--;
  }
  res->rc++;

  if(--elems->rc == 0)
    free_list( elems);

  *res__p = res;
  *__res_rc__p = &res->rc;
}
