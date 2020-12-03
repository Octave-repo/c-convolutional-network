#include "../matrice.h"
#include <stdio.h>

int conv1d(Matrice *in_feature_map, Matrice *kernel,
 unsigned short stride, unsigned short padding, Matrice *in_feature_ma);

int conv2d(Matrice *in_feature_map, Matrice *kernel,
 unsigned short stride, unsigned short padding, Matrice *in_feature_ma);