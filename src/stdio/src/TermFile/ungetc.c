/*
 *  implementation of class File
 */



#include "TermFile.h"


/*****************************************************************/


void SACungetc_TF(char c, FILE *stream)
{
  ungetc( c, stream);
}


/*****************************************************************/



