/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"



/*****************************************************************/

char *SACgetcwd()
{
  char *res;
  int size=100;
  char *success;
  
  res=(char *)SAC_MALLOC(size);
  
  success=getcwd(res, size);
  
  while (success!=NULL)
  {
    size*=2;
    SAC_FREE(res);
    res=(char *)SAC_MALLOC(size);
    success=getcwd(res, size);
  }
  
  return(res);
}
    


/*****************************************************************/

int SACchdir(char *name)
{
  int success;
  
  success=chdir(name);
  
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


int SACmkdir(char *name)
{
  int success;
  mode_t mask;
  
  mask=umask(0);
  umask(mask);
  
  success=mkdir(name, mask);
  
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


int SACrmdir(char *name)
{
  int success;
  
  success=rmdir(name);
  
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


