/*
 *  implementation of directory functions.
 */



#include "Dir.h"



/*****************************************************************/

int SACopendir( DIR ** stream, string name)
{
  int error = -1;

  *stream = opendir( name);

  if (*stream == NULL)
  {
    error = errno;
  }

  return( error);
}


/*****************************************************************/
