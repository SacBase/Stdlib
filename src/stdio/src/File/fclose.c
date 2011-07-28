/*
 *  implementation of class File
 */



#include "File.h"



/*****************************************************************/


void SACfclose(FILE **stream)
{
  int error=-1;
  
  error=fclose(*stream);
  
  if (error!=0)
  {
	 error=errno;
  }
}


/*****************************************************************/
