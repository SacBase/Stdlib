/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


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
