/*
 * Implementation of standard module Dir
 */

#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#include "sac.h"
#include "sacinterface.h"

typedef char* string;
