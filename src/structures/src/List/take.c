/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void _take( SAC_ND_KS_DEC_OUT_RC(list *, res), int n, SAC_ND_KS_DEC_IN_RC(list *, elems))
{
/*
 * we do have now:
 * - list **res__p;
 * -  int **res__rc__p;
 * -  int n;
 * - list *elems;
 * -  int *elems__rc;
 */
  list *new, *last;


  if( n<0)
    SAC_RuntimeError( "negative first arg of take\n");

  last = (list *)SAC_MALLOC(sizeof(list));
  last->rc = 1;
  last->rest = NULL;
#if TRACE
  fprintf( stderr, "creating NIL  at (%p)\n", last);
#endif


  if( n == 0) {
    *res__p = last;
    *res__rc__p = &last->rc;
    if(--elems->rc == 0)
      free_list( elems);
  }
  else {
    /*
     * Now, we do know that we have to take at least one element!
     */

    if( elems->rc == 1) { 
      /*
       * re-use all elems while rc==1 && n>0 !
       */
      *res__p = elems;
      *res__rc__p = elems__rc;
      do {
        if( elems->rest == NULL)
          SAC_RuntimeError( "first arg of take %d larger than length of list\n", n);
        new = elems;
        elems = elems->rest;
      }
      while( (--n>0) && ( elems->rc ==1));
      /*
       * Now, we decrement the "rest" of elems.
       */
      if(--elems->rc ==0)
        free_list(elems);
#if TRACE
      fprintf( stderr, "changing CONS at (%p)\n", new);
#endif
    }

    else {
      if( elems->rest == NULL)
        SAC_RuntimeError( "first arg of take %d larger than length of list\n", n);
      /* 
       * Now, we do know that we have at least one element to copy.
       * After doing so, we have to decrement the rc of elems !
       */
      new = (list *)SAC_MALLOC(sizeof(list));
      new->rc = 1;
      new->elem = elems->elem;
#if TRACE
      fprintf( stderr, "creating CONS at (%p)\n", new);
#endif
      *res__p = new;
      *res__rc__p = &new->rc;
      elems->rc--;
      elems = elems->rest; /* elems has to be one in advance of new ! */
      n--;
    }

    /*
     * new points to the last elem reused/ copied
     * elems is one in front!
     */
    while( n>0) {
      if( elems->rest == NULL)
        SAC_RuntimeError( "first arg of take %d larger than length of list\n", n);
      new->rest = (list *)SAC_MALLOC(sizeof(list));
#if TRACE
      fprintf( stderr, "       [ %d   .   (%p)]\n", new->elem, new->rest);
      fprintf( stderr, "creating CONS at (%p)\n", new->rest);
#endif
      new = new->rest;
      new->rc = 1;
      new->elem = elems->elem;
      elems = elems->rest;
      n--;
    }
    new->rest = last;
#if TRACE
    fprintf( stderr, "       [ %d   .   (%p)]\n", new->elem, new->rest);
#endif
  }
}



