/**
 * Dealing with sac_int arguments.
 */
#include <math.h>
#include "sacinterface.h"

double SAC_MATH_frexp( double val, sac_int *exp)
{
  int  ex;
  double res;

  res = frexp (val, &ex);

  *exp = (sac_int)ex;
  
  return res;
}

float SAC_MATH_frexpf( float val, sac_int *exp)
{
  int  ex;
  float res;

  res = frexpf (val, &ex);

  *exp = (sac_int)ex;

  return res;
}
