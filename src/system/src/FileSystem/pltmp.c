/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"

/*****************************************************************/

char *SACPtmpdir()
{
  char *result;

/* FIXME: CYGWINHACK temporarily broken to get the stdlib compiling under cygwin */
  result=(char *)SAC_MALLOC(strlen(P_tmpdir)+1);
  strcpy(result, P_tmpdir);

/* code from a commit, which is better though is not known by me HNV */
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


