/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


int nth( int n, SAC_ND_PARAM_in_rc( list *, elems))
{
  /*
   * we do have now:
   * -  int n;
   * - list *elems;
   * -  int *__elems_rc;
   */
  list *ptr;
  int res;

  if( n<0)
    SAC_RuntimeError( "negative first arg of nth\n");

  ptr = elems;
  while( n>0) {
    ptr=ptr->rest;
    if( ptr->rest == NULL)
      SAC_RuntimeError( "first arg of nth %d larger than length of list\n", n);
    n--;
  }
  res = ptr->elem;

  if(--elems->rc == 0) {
    free_list( elems);
  }

  return( res);
}
