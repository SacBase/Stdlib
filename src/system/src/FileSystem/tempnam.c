/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"



/*****************************************************************/

char *SACtempnam(char *dir, char *prefix)
{
  char *name;
  
  name=tempnam(dir, prefix);
  if (name==NULL)
  {
    name=(char*)SAC_MALLOC(1);
    *name=0;
  }
  
  return(name);
}


/*****************************************************************/
