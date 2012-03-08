/*
 *  implementation of process functions.
 */



#include "Process.h"



/*****************************************************************/

int SACpopen(FILE ** stream, char *command, char *mode)
{
  int error = -1;

  *stream = popen( command, mode);

  if (*stream == NULL)
  {
    error = errno;
  }

  return (error);
}


/*****************************************************************/
