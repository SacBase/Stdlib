/*
 * Implementation of class File
 */

#include "TermFile.h"

sac_int SACfputs_TF(char *s, FILE *stream)
{
    return (sac_int)fputs(s, stream);
}
