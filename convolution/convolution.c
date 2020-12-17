#include "convolution.h"

int conv1d(Matrice in_feature_map, Matrice kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map)
{
    int new_size;
    int tempint;
    int pos;

    tempint = in_feature_map.size - 2 + 2 * padding;
    new_size = tempint / stride;
    
    out_feature_map->dim = 1;
    out_feature_map->size = new_size;

    out_feature_map->matrice = malloc(sizeof(double*));
    out_feature_map->matrice[0] = malloc(sizeof(double) * new_size);

    pos = 0;
    for (int i = 1-padding ; i <= new_size ; i += stride){
        double somme = 0;
        for (int j = 0 ; j < kernel.size ; j++)
        {
            int half_size = (int) kernel.size/2;
            int x = i + (stride * j-1);
            //printf("%f\n", in_feature_map.matrice[0][x]);
            somme += (x >= 0 && x < in_feature_map.size) ? kernel.matrice[0][j] * in_feature_map.matrice[0][x] : 0;
        }
        printf("%.2f\n", somme);
        out_feature_map->matrice[0][pos++] = somme;
    }
    return 1;
}

int conv2d(Matrice *in_feature_map, Matrice *kernel,
 unsigned short stride, unsigned short padding, Matrice *in_feature_ma)
{
    return 1;
}

Matrice createMatrix(unsigned int size, unsigned int dim, double *tab)
{
    Matrice m;

    m.dim = dim;
    m.size = size;
    if (dim == 1)
    {
        m.matrice = malloc(sizeof(double *));
        m.matrice[0] = malloc(sizeof(double) * size);
        for (int i = 0 ; i < size ; i++)
        {
            m.matrice[0][i] = *(tab + i);
        }
    }
    if (dim == 2)
    {
        m.matrice = malloc(size * sizeof(double *));
        for (int i = 0 ; i < size ; i++)
        {
            m.matrice[i] = malloc(sizeof(double) * size);
            for (int j = 0 ; j < size ; j++)
                m.matrice[i][j] = *(tab + i * size + j);
        }
    }
    return m;
}

int main()
{
    Matrice m;
    double tab[1][6]  = {1,3,3,0,1,2};

    double tab2[1][3] = {2, 0, 1};

    conv1d(createMatrix(6, 1, tab[0]), createMatrix(3, 1, tab2[0]), 1, 0, &m);
    printf("%f\n", m.matrice[0][0]);
}