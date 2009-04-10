/*
 *  Implementation of module BinFile
 */


#include "BinFile.h"

#define array_nt (array, T_OLD((AUD, (NHD, (NUQ, )))))
#define ret_nt   (ret,   T_OLD((AUD, (NHD, (NUQ, )))))

void SACbinfReadDoubleArray( SAC_ND_PARAM_out( array_nt, double), int fd, int dim, int *shp)
{
  SAC_ND_DECL__DATA( ret_nt, double, )
  SAC_ND_DECL__DESC( ret_nt, )
  int SAC_ND_A_MIRROR_DIM( ret_nt) = dim;
  int i, size;
  int bytesRead;
  double *doublearray;
  int given_dim;
  int *given_shp;

  SAC_ND_ALLOC__DESC( ret_nt, dim)
  SAC_ND_SET__RC( ret_nt, 1)

    /*  start_token = PARSE_DOUBLE_ARRAY; */
    /*  yyin = stream; */
  given_dim = dim;
  given_shp = shp;
  for( i = 0, size = 1; i < dim; i++) {
    size *= shp[i];
    SAC_ND_A_DESC_SHAPE( ret_nt, i) = shp[i];
  }
  SAC_ND_A_DESC_SIZE( ret_nt) = size;
  doublearray = (double *) SAC_MALLOC( size * sizeof( double));

  /* read double array from file fd */
  bytesRead = read(fd,doublearray,size * sizeof(double));

  SAC_ND_A_FIELD( ret_nt) = doublearray;

  SAC_ND_RET_out( array_nt, ret_nt)
}

#undef array_nt
#undef ret_nt
