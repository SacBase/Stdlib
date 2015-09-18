#include <stdlib.h>

int SACsystem (char *command)
{
  const char *  cmd = command;
  return system (cmd);
}

