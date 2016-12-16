/*
 *  implementation of class File
 */



#include "TermFile.h"


/*****************************************************************/


int SACfscanf_TF(FILE *stream, char *format, ...)
{
  va_list args;
  int ret;

  va_start(args, format);
  ret = vfscanf( stream, format, args);
  va_end(args);

  return ret;
}


/*****************************************************************/



