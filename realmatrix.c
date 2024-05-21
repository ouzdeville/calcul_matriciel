
#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"



rmat init(int ligne, int colonne){

    rmat mat;
    int i=0;
    mat.rown=ligne;
    mat.coln=colonne;
    // je déclare un tableau contenant des tableaux (float *)
    // les lignes sont des tablaux de tablaux
    mat.coeff=(float **) malloc(mat.rown *sizeof(float *));
    for ( i = 0; i < mat.rown; i++)
    {
        // chaque ligne est un tableau de réel
        mat.coeff[i]= calloc(mat.coln, sizeof(float));
    }

    return mat;
}

rmat init_Id(int ordre){
    rmat mat;
    int i=0;
    mat=init(ordre, ordre);
     for ( i = 0; i < mat.rown; i++)
    {
        // chaque ligne est un tableau de réel
        mat.coeff[i][i]=1;
    }
    return mat;
}

void affiche(rmat A){
    int i,j;
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            printf("%0.2f \t", A.coeff[i][j]);
        }
        printf("\n");
        
    }
    

}

rmat add(rmat A, rmat B){
    rmat C=init(A.rown,A.coln);
    int i=0, j=0;
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            C.coeff[i][j]= A.coeff[i][j]+ B.coeff[i][j];
        }
        
    }
    
    return C;
}


rmat mult(rmat A, rmat B){
    rmat C=init(A.rown,B.coln);
    int i=0, j=0,k;
    for ( i = 0; i < C.rown; i++)
    {
        for ( j = 0; j < C.coln; j++)
        {
            for ( k = 0; k < A.coln; k++)
            {
                C.coeff[i][j]+= A.coeff[i][k]* B.coeff[k][j];
            }
            
            
        }
        
    }
    
    return C;

}
