/*
 *  implementation of class BinFile
 */



#include "BinFile.h"



/*****************************************************************/

int SACbinfopen(int *fd, char *name, int flags)
{
  int error=-1;
  
  *fd = open(name, flags, S_IRUSR | S_IWUSR);
  
  if (*fd==-1)
  {
	 error=errno;
  }
  
  return(error);
}


/*****************************************************************/



