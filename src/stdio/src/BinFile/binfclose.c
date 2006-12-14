/*
 *  implementation of class BinFile
 */



#include "BinFile.h"



/*****************************************************************/

int SACbinfclose(int fd)
{
  int error=-1;
  int retVal;
  retVal = close(fd);
  if (retVal==-1) {
    error=errno;
  }
  
  return(error);
}

/*****************************************************************/



