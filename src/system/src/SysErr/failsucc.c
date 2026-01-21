/*
 * Implementation of external standard module SysErr
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "sacinterface.h"

bool clear(sac_int err)
{
    return (err == -1);
}

bool fail(sac_int err)
{
    return (err != -1);
}
