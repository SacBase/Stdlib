#include <limits.h>


int minint()
{
  /* Due to a bug in limits.h (!!!), we have to use INT_MAX here!!! */
  return( /* INT_MIN */ 1 - INT_MAX);
}
