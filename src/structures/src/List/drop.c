/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void _drop( SAC_ND_KS_DEC_OUT_RC(list *, res), int n, SAC_ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now:
 * - list **res__p;
 * -  int **res__rc__p;
 * -  int n;
 * - list *elems;
 * -  int *elems__rc;
 */
  list * res=elems;

  if( n<0)
    SAC_RuntimeError( "negative first arg of drop\n");

  while( n>0) {
    if( res->rest == NULL)
      SAC_RuntimeError( "first arg of drop %d larger than length of list\n", n);
    res=res->rest;
    n--;
  }
  res->rc++;

  if(--elems->rc == 0)
    free_list( elems);

  *res__p = res;
  *res__rc__p = &res->rc;
}

