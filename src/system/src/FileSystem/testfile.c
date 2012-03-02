/*
 *  implementation of class FileSystem
 */



#include "FileSystem.h"



/*****************************************************************/

int SACisdir(int *success, char *name)
{
  struct stat buf;
  int result = 0;

  *success = stat(name, &buf);

  if (*success == -1)
  {
    *success = errno;
  }
  else
  {
    *success = -1;
    result = S_ISDIR(buf.st_mode);
  }

  return (result);
}


/*****************************************************************/

int SACisreg(int *success, char *name)
{
  struct stat buf;
  int result = 0;

  *success = stat(name, &buf);

  if (*success == -1)
  {
    *success = errno;
  }
  else
  {
    *success = -1;
    result = S_ISREG(buf.st_mode);
  }

  return (result);
}



/*****************************************************************/

int SACislnk(int *success, char *name)
{
  struct stat buf;
  int result = 0;

  *success = stat(name, &buf);

  if (*success == -1)
  {
    *success = errno;
  }
  else
  {
    *success = -1;
    result = S_ISLNK(buf.st_mode);
  }

  return (result);
}



/*****************************************************************/

unsigned long long SACfilesize(int *success, char *name)
{
  struct stat buf;
  unsigned long long result = 0;

  *success = stat(name, &buf);

  if (*success == -1)
  {
    *success = errno;
  }
  else
  {
    *success = -1;
    result = (unsigned long long) buf.st_size;
  }

  return (result);
}



/*****************************************************************/
