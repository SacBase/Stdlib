/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"


/*****************************************************************/

char *SACtmpnam()
{
  char *buffer, *name;
  
  buffer=tmpnam(NULL);
  name=(char *)MALLOC(strlen(buffer)+1);
  strcpy(name, buffer);
  
  return(name);
}


/*****************************************************************/
