/*
 * Implementation of class File
 */

#include "TermFile.h"

#ifdef SACARG_WORKS
SAC_C_EXTERN SACtypes *SACTYPE_String__string;
#endif

#ifdef SACARG_WORKS
sac_int SACfgets_TF(SACarg **str, sac_int size, FILE *stream)
#else
sac_int SACfgets_TF(char **str, sac_int size, FILE *stream)
#endif
{
    char *buf = malloc(sizeof(char) * (size_t)size);
    char *buf2 = fgets(buf, (int)size, stream);
    if (buf2 == NULL) {
        free (buf);
        return errno;
    }

#ifdef SACARG_WORKS
    *str = SACARGcreateFromPointer (SACTYPE_String__string, buf2, 1, 5);
#else
    *str = buf2;
#endif

    return -1;
}
