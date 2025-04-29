#include <stdlib.h>
#include <time.h>

unsigned long SAC_srand_time(void)
{
    unsigned long low_bits  = (unsigned long)time(NULL);
    unsigned long high_bits = (unsigned long)rand();
    return ((high_bits << 32) | low_bits);
}
