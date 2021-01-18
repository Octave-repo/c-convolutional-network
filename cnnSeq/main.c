#include "../matrice.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#define MAX 100
#define MIN 0


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
            printf("%.3f ", m.matrice[i][j]);
        }
        fgets(buffer, 255, f);
        printf("\n");
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


int main(int argc, char *argv[]){
    srand(time(NULL));
    /*
    if(argc != 3){
        return 0;
    }
    */
    loadMatrix("test.txt");
    writeMatrix("map32.txt", randomMatrix(32));
    writeMatrix("map64.txt", randomMatrix(64));
    writeMatrix("map128.txt", randomMatrix(128));
    writeMatrix("kernel3.txt", randomMatrix(3));
    writeMatrix("kernel7.txt", randomMatrix(7));
    writeMatrix("kernel9.txt", randomMatrix(9));




}
