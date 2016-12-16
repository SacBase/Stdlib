/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrspn( string first, string second)
{
  int res;

  res = strspn( first, second);

  return( res);
}

/*****************************************************************/
