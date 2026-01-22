/*
 * Implementation of class File
 */

#include "TermFile.h"

sac_int SACfputc_TF(char c, FILE *stream)
{
    return (sac_int)fputc(c, stream);
}
