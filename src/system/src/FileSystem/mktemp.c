#include <unistd.h>

char *
SACmkdtemp (char *  template)
{
  return mkdtemp (template);
}

int
SACmkstemp (char *  template)
{
  return mkstemp (template);
}
