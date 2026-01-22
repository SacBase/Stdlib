/*
 * Implementation of class File
 */

#include "TermFile.h"

sac_int SACscanf_TF(char *format, ...)
{
    va_list args;

    va_start(args, format);
    sac_int ret = (sac_int)vscanf(format, args);
    va_end(args);

    return ret;
}
