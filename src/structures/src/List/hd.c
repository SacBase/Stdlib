/*
 *  Implementation of SAC standard module List
 */


#include "List.h"




int hd(SAC_ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now: 
 * - list *elems;
 * -  int *__elems_rc;
 */
  int res;

  if( elems->rest == NULL)
    __SAC__Runtime_Error( "hd applied to NIL\n");
  res = elems->elem;

  if(--elems->rc == 0)
    free_list( elems);

  return(res);
}
