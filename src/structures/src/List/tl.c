/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


#ifdef TAGGED_ARRAYS

#define res_nt   (res,   (SCL, (HID, (NUQ,))))
#define elems_nt (elems, (SCL, (HID, (NUQ,))))

void tl( SAC_ND_PARAM_out( res_nt, list *),
         SAC_ND_PARAM_in( elems_nt, list *))
{
  SAC_ND_DECL__DESC( res_nt, )
  SAC_ND_DECL__DATA( res_nt, list *, )

  if (elems->rest == NULL) {
    SAC_RuntimeError( "tl applied to NIL\n");
  }
  res = elems->rest;

  (DESC_RC( res->desc))++;

  if (--(DESC_RC( elems->desc)) == 0) {
    free_list( elems);
  }

  SAC_ND_A_DESC( res_nt) = res->desc;
  SAC_ND_RET_out( res_nt, res_nt)
}

#undef res_nt
#undef elems_nt

#else  /* TAGGED_ARRAYS */

void tl( SAC_ND_PARAM_out_rc( list *, res),
         SAC_ND_PARAM_in_rc( list *, elems))
{
  /*
   * we do have now:
   * - list **res__p;
   * -  int **res__rc__p;
   * - list *elems;
   * -  int *elems__rc;
   */
  list *res;

  if (elems->rest == NULL) {
    SAC_RuntimeError( "tl applied to NIL\n");
  }
  res = elems->rest;

  (*(res->rc))++;

  if (--(*(elems->rc)) == 0) {
    free_list( elems);
  }
  
  *res__p = res;
  *res__rc__p = res->rc;
}

#endif  /* TAGGED_ARRAYS */
