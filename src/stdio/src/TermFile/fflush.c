/*
 * Implementation of class File
 */

#include "TermFile.h"

sac_int SACfflush_TF(FILE *f)
{
    return (sac_int)fflush(f);
}
