/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void free_list(list *elems)
{
  list *next;

  do {
    next = elems->rest;

#if TRACE
    fprintf( stderr, "freeing (%p)\n", elems);
#endif

    SAC_FREE( elems);
    elems = next;
  }while((elems != NULL) && (--elems->rc == 0));
}

