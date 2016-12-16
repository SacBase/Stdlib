/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrncmp( string first, string second, int n)
{
  int res;

  res = strncmp( first, second, n);

  return( res);
}

/*****************************************************************/
