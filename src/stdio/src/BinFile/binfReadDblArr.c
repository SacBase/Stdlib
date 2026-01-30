/*
 *  Implementation of module BinFile
 */


#include "BinFile.h"

SACarg *SACbinfReadDoubleArray(sac_int fd, sac_int dim, sac_int *shp)
{
  double *doublearray;

  sac_int size = 1;
  for (sac_int i = 0; i < dim; i++) {
    size *= shp[i];
  }
  doublearray = (double *)malloc(size * sizeof(double));

  /* read double array from file fd */
  ssize_t bytesRead = read((int)fd, doublearray, size * sizeof(double));

  return SACARGcreateFromPointer(SACTYPE__MAIN__double, doublearray, dim, shp);
}
