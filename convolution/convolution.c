#include "convolution.h"

int conv1d(Matrice in_feature_map, Matrice kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map)
{
    int new_size;
    int tempint;
    int pos;

    //On calcule la taille de la nouvelle matrice
    tempint = in_feature_map.size - 2 + 2 * padding;
    new_size = tempint / stride;
    
    //On initialise les données de la matrice
    out_feature_map->dim = 1;
    out_feature_map->size = new_size;
    //On initialise la matrice 
    out_feature_map->matrice = malloc(sizeof(double*));
    out_feature_map->matrice[0] = malloc(sizeof(double) * new_size);

    pos = 0;
    //On parcours la matrice d'entrée
    for (int i = 1-padding ; i <= new_size ; i += stride){
        double somme = 0;
        //Pour chaque éléments parcourus on fait les produits
        for (int j = 0 ; j < kernel.size ; j++)
        {
            int half_size = (int) kernel.size/2;
            int x = i + (stride * j-1);
            //Fait la somme en prennant en compte le padding
            somme += (x >= 0 && x < in_feature_map.size) ? kernel.matrice[0][j] * in_feature_map.matrice[0][x] : 0;
        }
        //!!!
        printf("%.2f\n", somme);
        out_feature_map->matrice[0][pos++] = somme;
    }
    return 1;
}

//Bordel ça a compile du premier coup
int conv2d(Matrice in_feature_map, Matrice kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map)
{
    int new_size;
    int tempint;
    int pos;
    int half_kern_size;

    half_kern_size = kernel.size/2;
    //On calcule la taille de la nouvelle matrice
    tempint = in_feature_map.size - 2 + 2 * padding;
    new_size = tempint / stride;
    
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
            for (int ii = -half_kern_size ; ii <= half_kern_size-(1-kernel.size%2) ; ii++)
            {
                for (int jj = -half_kern_size ; jj <= half_kern_size-(1-kernel.size%2) ; jj++)
                {
                    if (jj+centre_j >= 0 && jj+centre_j < in_feature_map.size && ii+centre_i >= 0 && ii+centre_i < in_feature_map.size)
                    {
                        somme += in_feature_map.matrice[ii+centre_i][jj+centre_j] * kernel.matrice[ii+half_kern_size][jj+half_kern_size];
                    }
                }
            }
            printf("%.2f ", somme);
            out_feature_map->matrice[i][j] = somme;
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
                m.matrice[i][j] = *(tab + i * size + j);
        }
    }
    return m;
}

int main()
{
    Matrice m1;
    Matrice m2;
    double mat1[1][6]  = {1, 3, 3, 0, 1, 2};
    double kernel1[1][3] = {2, 0, 1};

    double mat2[5][5] ={
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 1},
        {2, 3, 4, 5, 6},
        {7, 8, 9, 1, 2},
        {2, 3, 4, 5, 6}
    };
    double kernel2[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    conv1d(createMatrix(6, 1, mat1[0]), createMatrix(3, 1, kernel1[0]), 1, 0, &m1);
    printf("-------------------------------\n");
    m2 = createMatrix(5, 2, mat2[0]);
    conv2d(createMatrix(5, 2, mat2[0]), createMatrix(3, 2, kernel2[0]), 1, 0, &m2);
}