/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"



/*****************************************************************/

int SACrename(char *old, char *new)
{
  int success;
  
  success=rename(old, new);
  
  if (success==-1)
  {
    success=errno;
  }
  else
  {
    success=-1;
  }
  
  return(success);
}


/*****************************************************************/


