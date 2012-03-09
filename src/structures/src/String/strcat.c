/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

string SACstrcat( string first, string second)
{
  size_t len1;
  size_t len2;
  string new;

  len1 = strlen( first);
  len2 = strlen( second);
  new = (string) SAC_MALLOC( len1 + len2 + 1);

  strcpy( new, first);
  strcpy( new + len1, second);

  return( new);
}

/*****************************************************************/
