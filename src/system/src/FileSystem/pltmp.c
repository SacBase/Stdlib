/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"

/*****************************************************************/

char *SACPtmpdir( void)
{
  char *result;

  result=(char *)SAC_MALLOC(4);
  strcpy(result, "/tmp");
  
  return(result);
}


/*****************************************************************/

int SACLtmpnam( void)
{
  return(L_tmpnam);
}


/*****************************************************************/


