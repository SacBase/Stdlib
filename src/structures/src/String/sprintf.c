/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

string SACsprintf(string format, ...)
{
  va_list arg_p;
  static char buffer[2048];
  string new;
  
  va_start(arg_p, format);
  vsprintf(buffer, format, arg_p);
  va_end(arg_p);

  new=(string)RT_MALLOC(strlen(buffer)+1);
  strcpy(new, buffer);
  
  return(new);
}
 

  
  

/*****************************************************************/
