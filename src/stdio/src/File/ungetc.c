/*
 *  implementation of class File
 */



#include "File.h"


/*****************************************************************/


void SACungetc(char c, FILE *stream)
{
  ungetc( c, stream);
}


/*****************************************************************/



