/*
 *  implementation of standard module StringC
 */


#include "StringC.h"



/*****************************************************************/

int SACstrrchr(string str, char c)
{
  char *occur;
  
  occur=strrchr(str, c);
  
  if (occur==NULL)
  {
	 return(-1);
  }
  else
  {
	 return(occur-str);
  }
}



/*****************************************************************/


