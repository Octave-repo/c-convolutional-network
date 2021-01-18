#include "../matrice.h"
#include <stdio.h>
#include <stdlib.h>

int conv1d(Matrice in_feature_map, Matrice kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_ma);

int conv2d(Matrice in_feature_map, Matrice kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map);