/*
 *  Implementation of SAC standard module List
 */


#include "List.h"


void SAC_List_free_list( list *elems)
{
  list *next;

  do {
    next = elems->rest;

#if TRACE
    fprintf( stderr, "freeing (%p)\n", elems);
#endif

    SAC_FREE( elems);
    elems = next;
  }
  while ((elems != NULL) && (--(DESC_RC( elems->desc)) == 0));
}
