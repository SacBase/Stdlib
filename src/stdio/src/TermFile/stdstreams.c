/*
 *  implementation of standard class TermFile
 */



#include "TermFile.h"



/*****************************************************************/

void *SAC_create_stdin()
{
  return(stdin);
}


void *SAC_create_stdout()
{
  return(stdout);
}


void *SAC_create_stderr()
{
  return(stderr);
}


/*****************************************************************/


