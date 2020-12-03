#include "convolution.h"

int conv1d(Matrice *in_feature_map, Matrice *kernel,
 unsigned short stride, unsigned short padding, Matrice *in_feature_ma)
{
    int new_size;

    new_size = in_feature_map->size - 2 + 2 * padding;
    if (in_feature_map->dim != 1 && kernel->dim != 1)
        return 0;
    
    return 1;
}

int conv2d(Matrice *in_feature_map, Matrice *kernel,
 unsigned short stride, unsigned short padding, Matrice *in_feature_ma)
{
    return 1;
}

int main()
{
    printf("%d\n", 7/4);
}