/**
 * Dealing with sac_int arguments.
 */
#include <math.h>
#include "sacinterface.h"

double SAC_MATH_ldexp( double val, sac_int exp)
{
  return ldexp (val, (int)exp);
}

float SAC_MATH_ldexpf( float val, sac_int exp)
{
  return ldexpf (val, (int)exp);
}
