
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


int inverse(rmat A, rmat invA){

    
}

rmat init_Id(int ordre)
{
    rmat Id=init(ordre,ordre);
    for (int i = 0; i < ordre; i++)
    {
        Id.coeff[i][i]=1;
    }
    return Id;
}

rmat mult(rmat A, rmat B)
{
    
    rmat mat = init(B.rown, B.coln);
    for (int i = 0; i < A.rown; i++)
    {
        for (int j = 0; j < B.rown; j++)
        {
            float som=0;
            for (int k = 0; k < B.coln; k++)
            {
                som = som + A.coeff[i][k] * B.coeff[k][j];
            }
            mat.coeff[i][j]=som;
        }
    }
    return mat;
}

rmat add(rmat A, rmat B)
{
    rmat mat = init(B.rown, B.coln);
    for (int i = 0; i < A.rown; i++)
    {
        for (int j = 0; j < B.rown; j++)
        {
            mat.coeff[i][j]= A.coeff[i][j]  + B.coeff[i][j];
        }
    }
    return mat;
}

rmat transposition(rmat A)
{
    rmat mat = init(A.coln, A.rown);
    for (int i = 0; i < mat.rown; i++)
    {
        for (int j = 0; j < mat.coln; j++)
        {
            mat.coeff[i][j]=A.coeff[j][i];
        }
    }
    return mat;
}