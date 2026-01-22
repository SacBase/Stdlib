/*
 * Implementation of class TermFile
 */

#include "TermFile.h"

sac_int SACfprintf_TF(FILE *stream, char *format, ...)
{
    va_list args;

    va_start(args, format);
    sac_int ret = (sac_int)vfprintf( stream, format, args);
    va_end(args);

    return ret;
}
