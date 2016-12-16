/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

int SACsscanf( string s, string format, ...)
{
  int res;
  va_list arg_p;

  va_start( arg_p, format);
  res = vsscanf( s, format, arg_p);
  va_end( arg_p);

  return( res);
}

/*****************************************************************/
