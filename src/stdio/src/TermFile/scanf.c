/*
 *  implementation of class File
 */



#include "TermFile.h"


/*****************************************************************/


int SACfcanf_TF( char *format, ...)
{
  va_list args;
  int ret;

  va_start(args, format);
  ret = vscanf( format, args);
  va_end(args);

  return ret;
}


/*****************************************************************/



