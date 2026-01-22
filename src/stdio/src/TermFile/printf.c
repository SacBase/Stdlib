/*
 * Implementation of class TermFile
 */

#include "TermFile.h"

sac_int SACprintf_TF(char *format, ...)
{
    va_list args;

    va_start(args, format);
    sac_int ret = (sac_int)vprintf(format, args);
    va_end(args);

    return ret;
}
