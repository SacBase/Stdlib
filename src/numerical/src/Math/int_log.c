#include <math.h>

unsigned int SAC_MATH_log2u(unsigned int x)
{
#if defined __GNUC__ || defined __clang__
    int leading_zeroes = __builtin_clz(x);
#else
    int leading_zeroes = 0;
    unsigned int mask = 1u << (8 * sizeof(int) - 1);
    while (((mask & x) != mask) && mask != 0) {
        mask >>= 1;
        leading_zeroes++;
    }
#endif

    return 8 * sizeof(int) - leading_zeroes - 1;
}

unsigned long SAC_MATH_log2ul(unsigned long x)
{
#if defined __GNUC__ || defined __clang__
    int leading_zeroes = __builtin_clzl(x);
#else
    int leading_zeroes = 0;
    unsigned long mask = 1u << (8 * sizeof(unsigned long) - 1);
    while (((mask & x) != mask) && mask != 0) {
        mask >>= 1;
        leading_zeroes++;
    }
#endif

    return 8 * sizeof(unsigned long) - leading_zeroes - 1;
}
