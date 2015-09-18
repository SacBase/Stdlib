#include <stdlib.h>

char *
SACmktemp (char *  template)
{
  return mktemp (template);
}
