#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include "Constants.h"

#define UCHAR_MIN 0
#define USHRT_MIN 0
#define UINT_MIN 0
#define ULONG_MIN 0
#define ULLONG_MIN 0

//----------
#define minmax(rtype, SACtype, typeucase)	\
rtype max##SACtype( void )			\
{						\
  return( typeucase##_MAX);			\
}						\
						\
rtype min##SACtype( void )			\
{						\
  return( typeucase##_MIN);			\
}

#include "Constants.mac"
#undef minmax
//----------

sac_int maxint( void)
{
    sac_int num_bits = 8 * sizeof(sac_int);
    /**
     * To avoid overflow:
     * 2^(num_bits - 1) - 1 = 2 * 2^(num_bits - 2) - 1 = 
     * 2^(num_bits - 2) + (2^(num_bits - 2) - 1)
     **/
    sac_int half = (sac_int)1 << (num_bits - 2);
    return half + (half - 1);
}

sac_int minint( void)
{
    sac_int num_bits = 8 * sizeof(sac_int);
    return -((sac_int)1 << (num_bits - 1));
}

float minfloat( void)
{
  return( -FLT_MAX);  /* do not use FLT_MIN here!!! */
}

float maxfloat( void)
{
  return( FLT_MAX);
}

double mindouble( void)
{
  return( -DBL_MAX);
}

double maxdouble( void)
{
  return( DBL_MAX);
}

double tinydouble( void)
{
  return( DBL_MIN);
}

double epidouble( void)
{
    return( DBL_EPSILON);
}

sac_int randmax( void)
{
    return (sac_int)RAND_MAX;
}
