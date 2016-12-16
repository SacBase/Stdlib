/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrcspn( string first, string second)
{
  int res;

  res = strcspn( first, second);

  return( res);
}

/*****************************************************************/
