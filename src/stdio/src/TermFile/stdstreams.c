/*
 *  implementation of standard class TermFile
 */



#include "TermFile.h"



/*****************************************************************/

void *SACstdin;
void *SACstdout;
void *SACstderr;


/*****************************************************************/

void *create_stdin()
{
  return(stdin);
}


void *create_stdout()
{
  return(stdout);
}


void *create_stderr()
{
  return(stderr);
}


/*****************************************************************/
