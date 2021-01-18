#include "pooling.h"

int maxPool(Matrice in_feature_map, unsigned short kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map){
    int new_size;
    int pos;
    int half_kern_size;

    half_kern_size = kernel/2;
    //On calcule la taille de la nouvelle matrice
    new_size = kernel;

    //On initialise les données de la matrice
    out_feature_map->dim = 2;
    out_feature_map->size = new_size;
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
        out_feature_map->matrice[i] = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
    {
        for (int j = 0 ; j < new_size ; j++)
        {
            int centre_i = 1-padding + i + (i ? stride - 1 : 0);
            int centre_j = 1-padding + j + (j ? stride - 1 : 0);
            double max = -DBL_MAX;
            //Boucle imbriqué tel que le millieu des lignes et colones soient 0
            for (int ii = -half_kern_size ; ii <= half_kern_size-(1-kernel%2) ; ii++)
            {
                for (int jj = -half_kern_size ; jj <= half_kern_size-(1-kernel%2) ; jj++)
                {
                    if (jj+centre_j >= 0 && jj+centre_j < in_feature_map.size && ii+centre_i >= 0 && ii+centre_i < in_feature_map.size)
                    {
                        if(max < in_feature_map.matrice[ii+centre_i][jj+centre_j]){
                            max = in_feature_map.matrice[ii+centre_i][jj+centre_j];
                        }
                    }
                }
            }
            printf("%.2f ", max);
            out_feature_map->matrice[i][j] = max;
        }
        printf("\n");
    }
    return 1;

}

int minPool(Matrice in_feature_map, unsigned short kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map){
    int new_size;
    int pos;
    int half_kern_size;

    half_kern_size = kernel/2;
    //On calcule la taille de la nouvelle matrice
    new_size = kernel;

    //On initialise les données de la matrice
    out_feature_map->dim = 2;
    out_feature_map->size = new_size;
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
        out_feature_map->matrice[i] = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
    {
        for (int j = 0 ; j < new_size ; j++)
        {
            int centre_i = 1-padding + i + (i ? stride - 1 : 0);
            int centre_j = 1-padding + j + (j ? stride - 1 : 0);
            double min = DBL_MAX;
            //Boucle imbriqué tel que le millieu des lignes et colones soient 0
            for (int ii = -half_kern_size ; ii <= half_kern_size-(1-kernel%2) ; ii++)
            {
                for (int jj = -half_kern_size ; jj <= half_kern_size-(1-kernel%2) ; jj++)
                {
                    if (jj+centre_j >= 0 && jj+centre_j < in_feature_map.size && ii+centre_i >= 0 && ii+centre_i < in_feature_map.size)
                    {
                        if(min > in_feature_map.matrice[ii+centre_i][jj+centre_j]){
                            min = in_feature_map.matrice[ii+centre_i][jj+centre_j];
                        }
                    }
                }
            }
            printf("%.2f ", min);
            out_feature_map->matrice[i][j] = min;
        }
        printf("\n");
    }
    return 1;

}

int averagePool(Matrice in_feature_map, unsigned short kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map){
    int new_size;
    int pos;
    int half_kern_size;

    half_kern_size = kernel/2;
    //On calcule la taille de la nouvelle matrice
    new_size = kernel;

    //On initialise les données de la matrice
    out_feature_map->dim = 2;
    out_feature_map->size = new_size;
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
        out_feature_map->matrice[i] = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
    {
        for (int j = 0 ; j < new_size ; j++)
        {
            int centre_i = 1-padding + i + (i ? stride - 1 : 0);
            int centre_j = 1-padding + j + (j ? stride - 1 : 0);
            double somme = 0;
            //Boucle imbriqué tel que le millieu des lignes et colones soient 0
            for (int ii = -half_kern_size ; ii <= half_kern_size-(1-kernel%2) ; ii++)
            {
                for (int jj = -half_kern_size ; jj <= half_kern_size-(1-kernel%2) ; jj++)
                {
                    if (jj+centre_j >= 0 && jj+centre_j < in_feature_map.size && ii+centre_i >= 0 && ii+centre_i < in_feature_map.size)
                    {
                        somme += in_feature_map.matrice[ii+centre_i][jj+centre_j];
                    }
                }
            }
            double avg = somme/(kernel*kernel);
            printf("%.2f ", avg);
            out_feature_map->matrice[i][j] = avg;
        }
        printf("\n");
    }
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

    double tab[5][5]  = {
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5}
    };

    Matrice m2;
    m = createMatrix(5, 2, tab[0]);
    maxPool(m, 3, 1, 0, &m2);
    printf("\n");
    minPool(m, 3, 1, 0, &m2);
    printf("\n");
    averagePool(m, 3, 1, 0, &m2);
    printf("\n");
    return 0;


    /*

    double tab[4][4]  = {
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4},
        {1, 2, 3, 4}
    };

    Matrice m2;
    m = createMatrix(4, 2, tab[0]);
    maxPool(m, 2, 2, 0, &m2);
    printf("\n");
    minPool(m, 2, 2, 0, &m2);
    printf("\n");
    averagePool(m, 2, 2, 0, &m2);
    printf("\n");
    return 0;
    */
}
