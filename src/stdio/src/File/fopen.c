/*
 *  implementation of class File
 */



#include "File.h"



/*****************************************************************/

int SACfopen(FILE **stream, char *name, char *mode)
{
  int error=-1;
  
  *stream=fopen(name, mode);
  
  if (*stream==NULL)
  {
	 error=errno;
  }
  
  return(error);
}


/*****************************************************************/

