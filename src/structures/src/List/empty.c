/*
 *  Implementation of SAC standard module List
 */


#include "List.h"



int empty( SAC_ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now:
 * - list *elems;
 * -  int *__elems_rc;
 */

  int res;

  res = (elems->rest == NULL);

  if(--elems->rc == 0)
    free_list( elems);

  return( res);
}


