/*
 *  implementation of standard module StringC
 */


#include "StringC.h"
#include <limits.h>

/* Allow for long path names and URLs with long parameters. */
#if defined(PATH_MAX) && PATH_MAX >= 2048
#define BUFFER_SIZE     PATH_MAX
#else
#define BUFFER_SIZE     2048
#endif


/*****************************************************************/

string SACsprintf( string format, ...)
{
  va_list arg_p;
  char buffer[BUFFER_SIZE];
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
      new = (string) SAC_MALLOC( 1);
      new[0] = '\0';
  }

  return( new);
}

/*****************************************************************/
