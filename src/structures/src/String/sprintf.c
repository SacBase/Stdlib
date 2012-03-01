/*
 *  implementation of standard module StringC
 */


#include "StringC.h"


/*****************************************************************/

string SACsprintf( string format, ...)
{
  va_list arg_p;
  char buffer[2048];
  int n;
  string new;

  buffer[0] = '\0';
  va_start( arg_p, format);
  n = vsnprintf( buffer, sizeof buffer, format, arg_p);
  va_end( arg_p);
  if (n >= sizeof buffer) {
      new = (string) SAC_MALLOC( n + 1);
      va_start( arg_p, format);
      n = vsnprintf( new, n + 1, format, arg_p);
      va_end( arg_p);
  }
  else if (n >= 0) {
      new = (string) SAC_MALLOC( strlen( buffer) + 1);
      strcpy( new, buffer);
  }
  else {
      buffer[0] = '\0';
  }
  
  return( new);
}

/*****************************************************************/
