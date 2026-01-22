/*
 * Implementation of class File
 */

#include "TermFile.h"

sac_int SACfscanf_TF(FILE *stream, char *format, ...)
{
    va_list args;

    va_start(args, format);
    sac_int ret = (sac_int)vfscanf(stream, format, args);
    va_end(args);

    return ret;
}
