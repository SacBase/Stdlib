/*
 *  implementation of class TermFile
 */



#include "TermFile.h"



/*****************************************************************/

char* term_fscanl(FILE *stream, int length)
{
  char *input, *success;
  
  input=(char*)SAC_MALLOC(length+3);
  
  success=fgets(input, length+1, stream);
  
  if (success==NULL)
  {
    input[0]=0;
  }
    
  return(input);
}


/*****************************************************************/
