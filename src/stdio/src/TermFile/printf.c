/*
 *  implementation of class TermFile
 */



#include "TermFile.h"


/*****************************************************************/


void SACprintf(char *format, ...)
{
  va_list args;

  va_start(args, format);
  vprintf( format, args);
  va_end(args);
}


/*****************************************************************/



