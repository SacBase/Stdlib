/*
 *  implementation of class File
 */



#include "File.h"

#include <varargs.h>


/*****************************************************************/

void SACfprintf(FILE *stream, char *format, va_list args)
{
  fprintf( stream, format, args);
}


/*****************************************************************/



