/*
 *  implementation of external standard module SysErr
 */


#include <stdio.h>
#include <string.h>



/*****************************************************************/

int clear(int err)
{
  return(err==-1);
}

/*****************************************************************/

int fail(int err)
{
  return(err!=-1);
}

/*****************************************************************/


