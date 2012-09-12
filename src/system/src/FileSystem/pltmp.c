/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"

/*****************************************************************/

char *SACPtmpdir()
{
  char *result;

/* FIXME: CYGWINHACK temporarily broken to get the stdlib compiling under cygwin */
//  char *P_tmpdir = "";

  result=(char *)SAC_MALLOC(strlen(P_tmpdir)+1);
  strcpy(result, P_tmpdir);
  
  return(result);
}


/*****************************************************************/

int SACLtmpnam()
{
  return(L_tmpnam);
}


/*****************************************************************/


