#include <assert.h>

#include "sacinterface.h"
#include "BinFile.h"

sac_int SACbinfopen(int *fd, char *name, sac_int flags)
{
    *fd = open (name, flags, S_IRUSR | S_IWUSR);
    sac_int error = *fd == -1 ? errno : -1;
    return error;
}

sac_int SACbinfclose(int fd)
{
    int retVal = close (fd);
    int error = retVal == -1 ? errno : -1;
    return (sac_int) error;
}

sac_int SAC_O_RDONLY(void)
{
    return (sac_int) O_RDONLY;
}

sac_int SAC_O_WRONLY(void)
{
    return (sac_int) O_WRONLY;
}

sac_int SAC_O_RDWR(void)
{
    return (sac_int) O_RDWR;
}

sac_int SAC_O_CREAT(void)
{
    return (sac_int) O_CREAT;
}

sac_int SAC_O_TRUNC(void)
{
    return (sac_int) O_TRUNC;
}

SACarg *SACbinfReadDoubleArray (int fd, sac_int dim, sac_int *shp)
{
    size_t size = sizeof (double);
    for (sac_int i = 0; i < dim; i++) {
        size *= (size_t) (shp[i]);
    }

    double *data = (double *) malloc (size);
    ssize_t bytesRead = read (fd, data, size);

    if (bytesRead == -1) {
        SAC_RuntimeError ("Reading the file failed with error code %d\n", errno);
    }

    return SACARGcreateFromPointer (SACTYPE__MAIN__double, data, dim, shp);
}

void SACbinfWriteDoubleArray (int fd, sac_int dim, sac_int *shp, double *data)
{
    sac_int size = sizeof (double);
    for (sac_int i = 0; i < dim; i++) {
        size *= (size_t) (shp[i]);
    }

    ssize_t res = write (fd, data, size);

    if (res == -1) {
        SAC_RuntimeError ("Reading the file failed with error code %d\n", errno);
    }
}
