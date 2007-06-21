/*
 *  implementation of class File
 */



#include "File.h"
#include <string.h>
#include <stdlib.h>



/*****************************************************************/

int SACmkstemp(FILE **stream, char *template)
{
  int error=-1;
  char *tmp;
  int filedesc;

  tmp = SAC_MALLOC( sizeof( char) * strlen( template));
  strcpy( tmp, template);
  
  filedesc=mkstemp(tmp);
  
  SAC_FREE( tmp);

  if (filedesc == -1) {
    error = EIO;
  } else {
    *stream = fdopen( filedesc, "w+");

    if (*stream==NULL)
    {
	   error=errno;
    }
  }
  
  return(error);
}


/*****************************************************************/


