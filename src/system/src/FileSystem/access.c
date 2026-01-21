/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"



/*****************************************************************/



int SACaccess(int *success, char *name, sac_int how_in)
{
  int how = (int)how_in;
  int result, mode;

  switch (how)
  {
  case 0:
    mode=F_OK;
    break;
  case 1:
    mode=R_OK;
    break;
  case 2:
    mode=W_OK;
    break;
  case 3:
    mode=X_OK;
    break;
  default:
    mode=F_OK;
  }

  errno=0;

  result=access(name, mode);

  if (errno>0)
  {
    *success=errno;
  }
  else
  {
    *success=-1;
  }

  return(result==0);
}


/*****************************************************************/


