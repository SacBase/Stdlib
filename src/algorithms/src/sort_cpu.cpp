#include <thrust/execution_policy.h>
#include <thrust/sort.h>

extern "C" {
    void MySortDouble(double *keys, int *indices, int n)
    {
        thrust::sort_by_key(thrust::host, keys, keys + n, indices);
    }
}
