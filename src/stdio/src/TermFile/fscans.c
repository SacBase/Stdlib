/*
 * Implementation of class TermFile
 */

#include "TermFile.h"

char *term_fscans(FILE *stream, sac_int length)
{
    char format[32];
    char *input = (char *)SAC_MALLOC((size_t)length + 1);
    snprintf(format, sizeof(format), " %%%ds", (int)length);

    int success = fscanf(stream, format, input);
    if (success != 1)
    {
        input[0] = '\0';
    }

    return input;
}
