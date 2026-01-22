/*
 * Implementation of class TermFile
 */

#include "TermFile.h"

char *term_fscanl(FILE *stream, sac_int length)
{
    char *input= (char *)SAC_MALLOC((size_t)length + 3);
    char *success = fgets(input, (int)length + 1, stream);

    if (success == NULL)
    {
        input[0] = '\0';
    }

    return input;
}
