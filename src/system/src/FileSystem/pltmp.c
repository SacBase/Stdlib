/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"



/*****************************************************************/

char *SACPtmpdir()
{
  char *result;
  
  result=(char *)MALLOC(strlen(P_tmpdir)+1);
  strcpy(result, P_tmpdir);
  
  return(result);
}


/*****************************************************************/

int SACLtmpnam()
{
  return(L_tmpnam);
}


/*****************************************************************/
