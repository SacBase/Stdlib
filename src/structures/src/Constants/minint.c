#include <sacinterface.h>
#include <limits.h>

sac_int minint( void)
{
    sac_int num_bits = 8 * sizeof(sac_int);
    return -(sac_int)1 << (num_bits - 1);
}
