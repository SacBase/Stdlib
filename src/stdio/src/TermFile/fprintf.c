/*
 *  implementation of class TermFile
 */



#include "TermFile.h"


/*****************************************************************/


void SACfprintf_TF(FILE *stream, char *format, va_list args)
{
  vfprintf( stream, format, args);
}


/*****************************************************************/



