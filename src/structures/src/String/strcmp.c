/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrcmp( string first, string second)
{
  int res;

  res = strcmp( first, second);

  return( res);
}

/*****************************************************************/
