/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"

/*****************************************************************/

char *SACPtmpdir( void)
{
  char *result;

  const char tmp[] = "/tmp";
  const size_t l = strlen(tmp);

  result=(char *)SAC_MALLOC(l + 1); // null byte
  strcpy(result, tmp);
  
  return(result);
}


/*****************************************************************/
