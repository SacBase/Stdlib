/*
 * Implementation of class TermFile
 */

#include "TermFile.h"

void SACprintf_TF(char *format, ...)
{
    va_list args;

    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
