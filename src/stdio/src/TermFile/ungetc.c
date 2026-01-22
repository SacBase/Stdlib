/*
 * Implementation of class File
 */

#include "TermFile.h"

sac_int SACungetc_TF(char c, FILE *stream)
{
    return (sac_int)ungetc(c, stream);
}
