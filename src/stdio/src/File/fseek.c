/*
 *  implementation of class File
 */



#include "File.h"


/*****************************************************************/


void SACfseek(FILE *f, int off, int base)
{
  fseek( f, off, base);
}


/*****************************************************************/



