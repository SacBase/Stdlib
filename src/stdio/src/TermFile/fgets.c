/*
 *  implementation of class File
 */



#include "TermFile.h"

#ifdef SACARG_WORKS
SAC_C_EXTERN SACtypes *SACTYPE_String__string;
#endif

/*****************************************************************/

#ifdef SACARG_WORKS
int SACfgets_TF(SACarg **str, int size, FILE *stream)
#else
int SACfgets_TF(char **str, int size, FILE *stream)
#endif
{
    int error=-1;
    char *buf, *buf2;
    
    buf = malloc (sizeof(char) * size);
    buf2 = fgets (buf, size, stream);
    if (buf2 == NULL) {
        error = errno;
        free (buf);
    }
#ifdef SACARG_WORKS
    *str = SACARGcreateFromPointer (SACTYPE_String__string, buf2, 1, 5);
#else
    *str = buf2;
#endif
 
    return error;
}


/*****************************************************************/

