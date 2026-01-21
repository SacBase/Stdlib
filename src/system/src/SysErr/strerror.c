/*
 * Implementation of external standard module SysErr
 */

#include <stdio.h>
#include <string.h>

#include "sac.h"
#include "sacinterface.h"

char *SACstrerror(sac_int num)
{
    char *buf, *res;
    buf = strerror((int)num);
    res = (char *)SAC_MALLOC(strlen(buf) + 1);
    strcpy(res, buf);
    return res;
}
