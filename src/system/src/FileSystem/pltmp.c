/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"

/*****************************************************************/

char *SACPtmpdir()
{
  char *result;

  // P_tmpdir is an obsolete feature. It should really not be used at all.

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


