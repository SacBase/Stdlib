#include <unistd.h>

char *
SACmkdtemp (char *  template)
{
  return mkdtemp (template);
}

