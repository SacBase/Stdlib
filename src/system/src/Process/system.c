#include <sacinterface.h>
#include <stdlib.h>

sac_int SACsystem (char *command)
{
  const char *  cmd = command;
  return (sac_int)system (cmd);
}

