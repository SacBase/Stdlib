/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"

/*****************************************************************/

char *SACPtmpdir()
{
  char *result;

  result=(char *)SAC_MALLOC(4);
  strcpy(result, "/tmp");
  
  return(result);
}


/*****************************************************************/

int SACLtmpnam()
{
  return(L_tmpnam);
}


/*****************************************************************/


