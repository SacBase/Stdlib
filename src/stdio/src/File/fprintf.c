/*
 *  implementation of class File
 */



#include "File.h"


/*****************************************************************/


void SACfprintf(FILE *stream, char *format, ...)
{
  va_list args;

  va_start(args, format);
  vfprintf( stream, format, args);
  va_end(args);
}


/*****************************************************************/



