/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"



/*****************************************************************/


int SACremove(char *name)
{
  int success;
  
  success=remove(name);
  
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


