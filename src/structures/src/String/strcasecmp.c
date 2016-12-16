/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrcasecmp( string first, string second)
{
  int res;

  res = strcasecmp( first, second);

  return( res);
}

/*****************************************************************/
