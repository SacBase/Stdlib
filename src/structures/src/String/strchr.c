/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACstrchr( string str, char c)
{
  char *occur;

  occur = strchr( str, c);

  if (occur == NULL) {
    return( -1);
  }
  else {
    return( occur - str);
  }
}

/*****************************************************************/
