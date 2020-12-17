#include <math.h>
#include "../matrice.h"

int sigmoid(Matrice *in_feature_map, Matrice *out_feature_map);
int tanh_(Matrice *in_feature_map, Matrice *out_feature_map);
int relu(Matrice *in_feature_map, Matrice *out_feature_map);

double f_sigmoid(double x);
double f_tanh(double x);
double f_relu(double x);