/*
 *  implementation of class File
 */



#include "File.h"
#include <string.h>
#include <stdlib.h>



/*****************************************************************/

int SACmkstemp(FILE **stream, char ** name, char *template)
{
  int error=-1;
  int filedesc;

  *name = SAC_MALLOC( sizeof( char) * strlen( template));
  strcpy( *name, template);
  
  filedesc=mkstemp(*name);

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


