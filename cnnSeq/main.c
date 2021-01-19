#include "../matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX 100
#define MIN -100


int matrixSize(char* str){
    int size = 0;
    char* buf = strtok(str, ";");
    while(buf!=NULL){
        size++;
        buf = strtok(NULL, ";");
    }
    return(size);
}

Matrice loadMatrix(char* chemin){
    Matrice m;
    char buffer[255];
    FILE *f = fopen(chemin, "r+");
    fgets(buffer, 255, f);
    fclose(f);
    m.dim = 2;
    m.size = matrixSize(buffer);
    m.matrice = malloc(m.size*sizeof(double*));

    for(int i = 0; i<m.size; i++)
        m.matrice[i]= malloc(m.size*sizeof(double));

    f = fopen(chemin, "r+");
    fgets(buffer, 255, f);

    for(int i = 0; i < m.size; i++){
        char* buf = strtok(buffer, ";");
        for(int j = 0; j < m.size; j++){
            m.matrice[i][j] = strtod(buf, NULL);
            buf = strtok(NULL, ";");
        }
        fgets(buffer, 255, f);
    }
    fclose(f);
    return(m);
}

void writeMatrix(char* chemin, Matrice input){
    FILE *f = fopen(chemin, "w+");
    for(int i = 0; i < input.size; i++){
        for(int j = 0; j < input.size; j++){
            fprintf(f, "%.3f", input.matrice[i][j]);
            if(j != input.size-1)
                fprintf(f, ";");
        }
        if(i != input.size-1)
            fprintf(f, "\n");
    }
    fclose(f);
}

Matrice randomMatrix(unsigned int size){
    Matrice m;
    m.size = size;
    m.dim = 2;


    m.matrice = malloc(m.size*sizeof(double*));

    for(int i = 0; i<m.size; i++)
        m.matrice[i]= malloc(m.size*sizeof(double));

    for(int i = 0; i < m.size; i++){
        for(int j = 0; j < m.size; j++){
            m.matrice[i][j] = (double)(rand() % (MAX - MIN + 1)) + MIN;
        }
    }

    return m;
}

//###########################################################
//#####################CONVOLUTION############################
//###########################################################

int conv1d(Matrice in_feature_map, Matrice kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map)
{
    int new_size;
    int tempint;
    int pos;

    //On calcule la taille de la nouvelle matrice
    tempint = in_feature_map.size - 2 + 2 * padding;
    new_size = tempint / stride;

    //On initialise les donn�es de la matrice
    out_feature_map->dim = 1;
    out_feature_map->size = new_size;
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*));
    out_feature_map->matrice[0] = malloc(sizeof(double) * new_size);

    pos = 0;
    //On parcours la matrice d'entr�e
    for (int i = 1-padding ; i <= new_size ; i += stride){
        double somme = 0;
        //Pour chaque �l�ments parcourus on fait les produits
        for (int j = 0 ; j < kernel.size ; j++)
        {
            int half_size = (int) kernel.size/2;
            int x = i + (stride * j-1);
            //Fait la somme en prennant en compte le padding
            somme += (x >= 0 && x < in_feature_map.size) ? kernel.matrice[0][j] * in_feature_map.matrice[0][x] : 0;
        }
        out_feature_map->matrice[0][pos++] = somme;
    }
    return 1;
}

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
  new_size = (tempint / stride)+(tempint%stride?1:0);

    //On initialise les donn�es de la matrice
    out_feature_map->dim = 2;
    out_feature_map->size = new_size;
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
        out_feature_map->matrice[i] = malloc(sizeof(double) * new_size);
    for (int i = 0 ; i < new_size ; i++)
    {
        for (int j = 0 ; j < new_size ; j++)
        {
            int centre_i = 1-padding + i + (i ? stride - 1 : 0);
            int centre_j = 1-padding + j + (j ? stride - 1 : 0);
            double somme = 0;
            //Boucle imbriqu� tel que le millieu des lignes et colones soient 0
            for (int ii = -half_kern_size ; ii <= half_kern_size ; ii++)
            {
                for (int jj = -half_kern_size ; jj <= half_kern_size ; jj++)
                {
                    if (jj+centre_j >= 0 && jj+centre_j < in_feature_map.size && ii+centre_i >= 0 && ii+centre_i < in_feature_map.size)
                    {
                        somme += in_feature_map.matrice[ii+centre_i][jj+centre_j] * kernel.matrice[ii+half_kern_size][jj+half_kern_size];
                    }
                }
            }
            out_feature_map->matrice[i][j] = somme;
        }
    }
    return 1;
}

//###########################################################
//###########################################################
//###########################################################

//###########################################################
//#####################POOLING###############################
//###########################################################
int maxPool(Matrice in_feature_map, unsigned short kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map){
    int new_size;
    int tempint;
    int pos;
    int half_kern_size;

    half_kern_size = kernel/2;
    //On calcule la taille de la nouvelle matrice
    tempint = in_feature_map.size - 2 + 2 * padding;
    new_size = (tempint / stride)+(tempint%stride?1:0);

    //On initialise les donn�es de la matrice
    out_feature_map->dim = 2;
    out_feature_map->size = new_size;
    printf("%d\n", new_size);
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
        out_feature_map->matrice[i] = malloc(sizeof(double) * new_size);
    for (int i = 0 ; i < new_size ; i++)
    {
        for (int j = 0 ; j < new_size ; j++)
        {
            int centre_i = 1-padding + i + (i ? stride - 1 : 0);
            int centre_j = 1-padding + j + (j ? stride - 1 : 0);
            double max = -DBL_MAX;
            //Boucle imbriqu� tel que le millieu des lignes et colones soient 0
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
            out_feature_map->matrice[i][j] = max;
        }
    }
    return 1;

}

int minPool(Matrice in_feature_map, unsigned short kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map){
   int new_size;
   int tempint;
   int pos;
   int half_kern_size;

   half_kern_size = kernel/2;
   //On calcule la taille de la nouvelle matrice
   tempint = in_feature_map.size - 2 + 2 * padding;
   new_size = (tempint / stride)+(tempint%stride?1:0);

    //On initialise les donn�es de la matrice
    out_feature_map->dim = 2;
    out_feature_map->size = new_size;
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
        out_feature_map->matrice[i] = malloc(sizeof(double) * new_size);
    for (int i = 0 ; i < new_size ; i++)
    {
        for (int j = 0 ; j < new_size ; j++)
        {
            int centre_i = 1-padding + i + (i ? stride - 1 : 0);
            int centre_j = 1-padding + j + (j ? stride - 1 : 0);
            double min = DBL_MAX;
            //Boucle imbriqu� tel que le millieu des lignes et colones soient 0
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
            out_feature_map->matrice[i][j] = min;
        }
    }
    return 1;

}

int averagePool(Matrice in_feature_map, unsigned short kernel,
 unsigned short stride, unsigned short padding, Matrice *out_feature_map){
   int new_size;
   int tempint;
   int pos;
   int half_kern_size;

   half_kern_size = kernel/2;
   //On calcule la taille de la nouvelle matrice
   tempint = in_feature_map.size - 2 + 2 * padding;
   new_size = (tempint / stride)+(tempint%stride?1:0);

    //On initialise les donn�es de la matrice
    out_feature_map->dim = 2;
    out_feature_map->size = new_size;
    //On initialise la matrice
    out_feature_map->matrice = malloc(sizeof(double*) * new_size);
    for (int i = 0 ; i < new_size ; i++)
        out_feature_map->matrice[i] = malloc(sizeof(double) * new_size);
    for (int i = 0 ; i < new_size ; i++)
    {
        for (int j = 0 ; j < new_size ; j++)
        {
            int centre_i = 1-padding + i + (i ? stride - 1 : 0);
            int centre_j = 1-padding + j + (j ? stride - 1 : 0);
            double somme = 0;
            //Boucle imbriqu� tel que le millieu des lignes et colones soient 0
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
            out_feature_map->matrice[i][j] = avg;
        }
    }
    return 1;
}

//###########################################################
//###########################################################
//###########################################################

//###########################################################
//#####################ACTIVATION############################
//###########################################################

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

//Applique la fonction f_sigmoid à la matrice in_feature_map et met le résultat dans out_feature_map
int sigmoid(Matrice *in_feature_map, Matrice *out_feature_map){
    int size = in_feature_map->size;
    int dim = in_feature_map->dim;
    //Dimension 2
    if(dim>1){
        for(int i=0; i<size; i++){
            for (int j=0; j<size;j++){
                out_feature_map->matrice[i][j] = f_sigmoid(in_feature_map->matrice[i][j]);
            }
        }
    //Dimension 1
    }else{
        for(int i=0; i<size; i++){
            out_feature_map->matrice[0][i] = f_sigmoid(in_feature_map->matrice[0][i]);
        }
    }
    return 0;
}

//Applique la fonction f_tanh à la matrice in_feature_map et met le résultat dans out_feature_map
int tanh_(Matrice *in_feature_map, Matrice *out_feature_map){
    int size = in_feature_map->size;
    int dim = in_feature_map->dim;
    //Dimension 2
    if(dim>1){
        for(int i=0; i<size; i++){
            for (int j=0; j<size;j++){
                out_feature_map->matrice[i][j] = f_tanh(in_feature_map->matrice[i][j]);
            }
        }
    //Dimension 1
    }else{
        for(int i=0; i<size; i++){
            out_feature_map->matrice[0][i] = f_tanh(in_feature_map->matrice[0][i]);
        }
    }
    return 0;
}

//Applique la fonction f_relu à la matrice in_feature_map et met le résultat dans out_feature_map
int relu(Matrice *in_feature_map, Matrice *out_feature_map){
    int size = in_feature_map->size;
    int dim = in_feature_map->dim;
    //Dimension 2
    if(dim>1){
        for(int i=0; i<size; i++){
            for (int j=0; j<size;j++){
                out_feature_map->matrice[i][j] = f_relu(in_feature_map->matrice[i][j]);
            }
        }
    //Dimension 1
    }else{
        for(int i=0; i<size; i++){
            out_feature_map->matrice[0][i] = f_relu(in_feature_map->matrice[0][i]);
        }
    }
    return 0;
}

//###########################################################
//###########################################################
//###########################################################

void writeTiming(char* label, int timestamp){
    FILE *f = fopen("timing.csv", "w+");
    fprintf(f, label);
    fprintf(f, ";%d", timestamp);
    fprintf(f, "\n");
    fclose(f);
}


int main(int argc, char *argv[]){

    srand(time(NULL));

    writeMatrix("map32.txt", randomMatrix(32));
    writeMatrix("map64.txt", randomMatrix(64));
    writeMatrix("map128.txt", randomMatrix(128));
    writeMatrix("kernel3.txt", randomMatrix(3));
    writeMatrix("kernel7.txt", randomMatrix(7));
    writeMatrix("kernel9.txt", randomMatrix(9));

    /*
    if(argc != 3){
        return 0;
    }
    */
    Matrice mapIn = loadMatrix("map32.txt");
    Matrice mapOut;
    Matrice kernel = loadMatrix("kernel3.txt");
    conv2d(mapIn, kernel, 1, 0, &mapOut);
    mapIn = mapOut;
    relu(&mapIn, &mapOut);
    mapIn = mapOut;
    maxPool(mapIn, kernel.size,3,2,&mapOut);
    writeMatrix("out.txt", mapOut);


    mapIn = loadMatrix("map32.txt");
    kernel = loadMatrix("kernel3.txt");
    conv2d(mapIn, kernel, 1, 0, &mapOut);
    mapIn = mapOut;
    writeMatrix("out3.txt", mapOut);
    sigmoid(&mapIn, &mapOut);
    mapIn = mapOut;
    averagePool(mapIn, kernel.size,3,0,&mapOut);
    writeMatrix("out2.txt", mapOut);


    return 0;
}
