#include <float.h>

/* !! This function does not return DBL_MIN !!
 * The reason for this is that DBL_MIN is the smallest
 * normalised value that can represented. For consistency
 * with maxint() and minint(), this function returns the
 * lowest negative number that can be represented, which
 * is the exact opposite of DBL_MAX: -DBL_MAX.
 *
 * To get DBL_MIN, look at tinydouble()
 *
 * More information can be found at:
 * http://forums.codeguru.com/showthread.php?260921-DBL_MIN-and-DBL_MAX&p=799431#post799431
 */
double mindouble()
{
  return( -DBL_MAX);
}
