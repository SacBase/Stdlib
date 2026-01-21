/*
 * Implementation of directory functions.
 */

#include "Dir.h"

sac_int SACopendir(DIR **stream, string name)
{
    sac_int err = -1;

    *stream = opendir(name);

    if (*stream == NULL)
    {
        err = errno;
    }

    return err;
}
