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

  result=(char *)SAC_MALLOC(l);
  strcpy(result, tmp);
  
  return(result);
}


/*****************************************************************/
