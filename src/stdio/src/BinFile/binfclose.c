/*
 *  implementation of class BinFile
 */



#include "BinFile.h"



/*****************************************************************/

int SACbinfclose(int fd)
{
  int error;
  
  error = close(fd);
  
  return(error);
}


/*****************************************************************/



