/*
 *  Implementation of module BinFile
 */


#include "BinFile.h"

#define array_nt (array, (AUD, (NHD, (NUQ, ))))
#define ret_nt   (ret,   (AUD, (NHD, (NUQ, ))))

void SACbinfWriteDoubleArray(int fd, int dim, int *shp, double* array)
{
  int i,size;
  ssize_t res;
  for( i = 0, size = 1; i < dim; i++) {
    size *= shp[i];
  }

  res = write(fd,array,size*sizeof(double));
  if( (int)res != size*sizeof(double)) {
    SAC_RuntimeWarning( "only managed to write %d bytes of a %d byte array of doubles",
                         res, size*sizeof(double));
  }
}

#undef array_nt
#undef ret_nt
