/*
 *  implementation of class File
 */



#include "File.h"



/*****************************************************************/

char* fscans(FILE *stream, int length)
{
  int success;
  char *input, *format;
  
  input=(char*)MALLOC(length+1);
  format=(char*)MALLOC(32);
  sprintf(format, "%%%ds", length);
  
  success=fscanf(stream, format, input);
  
  if (success!=1)
  {
    input[0]=0;
  }
    
  return(input);
}


/*****************************************************************/
