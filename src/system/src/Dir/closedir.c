/*
 * Implementation of directory functions.
 */

#include "Dir.h"

void SACclosedir(DIR* stream)
{
    closedir(stream);
}
