/*
 *  Implementation of SAC standard module List
 */


#include "List.h"



void nil(SAC_ND_KS_DEC_OUT_RC(list *, res))
{
/*
 * we do have now: 
 * - list **res__p;
 * -  int **res__rc__p;
 */
  list *res;

  res = (list *)SAC_MALLOC(sizeof(list));
  res->rc = 1;
  res->rest = NULL;

#if TRACE
    fprintf( stderr, "creating NIL  at (%p)\n", res);
#endif

  *res__p = res;
  *res__rc__p = &res->rc;

}

