/*
 *  implementation of class File
 */



#include "File.h"



/*****************************************************************/

char* fscanl(FILE *stream, int length)
{
  char *input, *success;
  
  input=(char*)MALLOC(length+3);
  
  success=fgets(input, length+1, stream);
  
  if (success==NULL)
  {
    input[0]=0;
  }
    
  return(input);
}


/*****************************************************************/
