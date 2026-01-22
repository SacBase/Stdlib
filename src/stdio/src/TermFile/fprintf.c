/*
 * Implementation of class TermFile
 */

#include "TermFile.h"

void SACfprintf_TF(FILE *stream, char *format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf( stream, format, args);
    va_end(args);
}
