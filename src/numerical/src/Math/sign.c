#include <math.h>

int SAC_MATH_sign(double X)
{
  return copysign(1.0, X);
}

int SAC_MATH_signf(float X)
{
  return copysign(1.0, (double)X);
}
