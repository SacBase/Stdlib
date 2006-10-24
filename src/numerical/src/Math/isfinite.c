/**
 * Proper C function wrappers around MACROS.
 */
#include <math.h>

int SAC_MATH_isfinite( double X)
{
  return( isfinite( X));
}
