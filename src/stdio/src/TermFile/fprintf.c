/*
 *  implementation of class TermFile
 */



#include "TermFile.h"

#include <varargs.h>


/*****************************************************************/

void SACfprintf_TF(FILE *stream, char *format, va_list args)
{
  fprintf( stream, format, args);
}


/*****************************************************************/



