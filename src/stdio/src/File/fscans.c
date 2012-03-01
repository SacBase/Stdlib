/*
 *  implementation of class File
 */



#include "File.h"



/*****************************************************************/

char* fscans(FILE* stream, int length)
{
  int success;
  char *input;
  char format[32];

  input = (char *) SAC_MALLOC(length + 1);
  snprintf(format, sizeof format, " %%%ds", length);

  success = fscanf(stream, format, input);

  if (success != 1)
  {
    input[0] = 0;
  }

  return (input);
}


/*****************************************************************/
