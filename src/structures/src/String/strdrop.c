/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

string strdrop( string old, int n)
{
  string new;

  RANGECHECK( (size_t) n, 0, strlen( old), old);

  new = (string) SAC_MALLOC( strlen( old) - n + 1);
  strcpy( new, old + n);

  return( new);
}

/*****************************************************************/
