#include <unistd.h>  // needed on OSX
#include <stdlib.h>  // needed on linux

char *
SACmkdtemp (char *  template)
{
  return mkdtemp (template);
}

