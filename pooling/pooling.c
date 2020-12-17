#include <stdio.h>
#include <stdlib.h>
#include "pooling.h"

int maxPool(Matrice *in_feature_map, unsigned short kernel_size, unsigned short stride, unsigned short padding,double **in_feature_ma){
    int parcoursX = 0;
    int parcoursY = 0;
    for (int i = parcoursX; i < kernel_size; i++){
        for (int j = parcoursY; j < kernel_size; j++){
            printf("Valeur de la cellule %i;%i = %f\n", i, j, in_feature_map.matrice[i][j]);
        }
    }

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
            {
                m.matrice[i][j] = *(tab + i * size + j);
            }
        }
    }

    return m;
}


int main()
{
    Matrice m;
    double tab[3][3]  = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    m = createMatrix(3, 2, tab[0]);
    printf("%f", m.matrice[1][1]);
    maxPool(tab, 2, 0, 0, tab);
    return 0;
}
