/*
 *  implementation of class File
 */



#include "File.h"


/*****************************************************************/


void SACfprintf(FILE *stream, char *format, va_list args)
{
  vfprintf( stream, format, args);
}


/*****************************************************************/



