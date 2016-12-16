/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrncasecmp( string first, string second, int n)
{
  int res;

  res = strncasecmp( first, second, n);

  return( res);
}

/*****************************************************************/
