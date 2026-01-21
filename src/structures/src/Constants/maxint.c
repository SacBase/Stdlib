#include <sacinterface.h>

#include <stdint.h>

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
