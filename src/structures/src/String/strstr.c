/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrstr( string haystack, string needle)
{
  string found = strstr( haystack, needle);
  return (found) ? (found - haystack) : -1;
}

/*****************************************************************/
