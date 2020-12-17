#include "activation.h"
#include <stdio.h>

int sigmoid(Matrice *in_feature_map, Matrice *out_feature_map){
    int size = in_feature_map->size;
    int dim = in_feature_map->dim;
    for(int i=0; i<dim; i++){
        for (int j=0; j<size;j++){
            out_feature_map->matrice[i][j] = f_sigmoid(in_feature_map->matrice[i][j]);
        }
    }
    return 0;
}

int tanh_(Matrice *in_feature_map, Matrice *out_feature_map){
    int size = in_feature_map->size;
    int dim = in_feature_map->dim;
    for(int i=0; i<dim; i++){
        for (int j=0; j<size;j++){
            out_feature_map->matrice[i][j] = f_tanh(in_feature_map->matrice[i][j]);
        }
    }
    return 0;
}

int relu(Matrice *in_feature_map, Matrice *out_feature_map){
    int size = in_feature_map->size;
    int dim = in_feature_map->dim;
    for(int i=0; i<dim; i++){
        for (int j=0; j<size;j++){
            out_feature_map->matrice[i][j] = f_tanh(in_feature_map->matrice[i][j]);
        }
    }
    return 0;
}

double f_sigmoid(double x){
    return 1/(1+exp(-x));
}

double f_tanh(double x){
    return (exp(x)-exp(-x))/(exp(x)+exp(-x));
}

double f_relu(double x){
    if (x<0) return 0;
    return x;
}

int main(){

}