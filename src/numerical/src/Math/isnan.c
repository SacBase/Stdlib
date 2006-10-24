/**
 * Proper C function wrappers around MACROS.
 */
#include <math.h>

int SAC_MATH_isnan( double X)
{
  return( isnan( X));
}
