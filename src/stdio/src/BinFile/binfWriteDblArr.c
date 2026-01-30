/*
 *  Implementation of module BinFile
 */


#include "BinFile.h"

void SACbinfWriteDoubleArray(sac_int fd, sac_int dim, sac_int *shp, double *array)
{
  sac_int size = 1;
  for (sac_int i = 0; i < dim; i++) {
    size *= shp[i];
  }

  ssize_t res = write((int)fd, array, size*sizeof(double));

  if (res != (ssize_t)(size * sizeof(double))) {
    SAC_RuntimeWarning("only managed to write %zd bytes of a" 
                       "%" PRIisac " byte array of doubles",
                       res, size * sizeof(double));
  }
}
