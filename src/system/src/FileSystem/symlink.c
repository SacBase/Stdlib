/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"


extern int symlink(const char *old, const char *new);



/*****************************************************************/


int SACsymlink(char *name, char *link)
{
  int success;
  
  success=symlink(name, link);
  
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


