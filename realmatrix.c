
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
    rmat C;
    int i,j;
    if (A.rown!=B.rown || A.coln!=B.coln){
        printf("l'addition de deux matrices n'est possible que si les deux matrices ont le même nombre de lignes et de colonnes\n");
        exit(1);
    }
    C=init(A.rown, A.coln);
    for ( i = 0; i < A.rown; i++){
        for ( j = 0; j < A.coln; j++){
            C.coeff[i][j]=A.coeff[i][j]+B.coeff[i][j];
        }
        
    }
    return C;
}

rmat mult(rmat A, rmat B){
    rmat D;
    int i,j,k;
    if (A.coln!=B.rown){
        printf("la multiplication de deux matrices n'est possible que si le nombre de colonnes de la première A.coeff est égal au nombre de lignes de la deuxième A.coeff\n");
        exit(1);
    }
    D=init(A.rown, B.coln);
    for ( i = 0; i < A.rown; i++){
        for ( j = 0; j < B.coln; j++){
            D.coeff[i][j]=0;
            for ( k = 0; k < A.coln; k++){
                D.coeff[i][j]+=A.coeff[i][k]*B.coeff[k][j];
            }
        }
        
    }
    return D;
}

rmat transposition(rmat A){
    rmat T;
    int i,j;
    T=init(A.coln, A.rown);
    for ( i = 0; i < A.rown; i++){
        for ( j = 0; j < A.coln; j++){
            T.coeff[j][i]=A.coeff[i][j];
        }
        
    }
    return T;
}

float det(rmat A){
    float det;
    if (A.rown!=A.coln){
        printf("le déterminant n'est défini que pour les matrices carrées\n");
        exit(1);
    }else {
        det=A.coeff[0][0]*A.coeff[1][1]-A.coeff[0][1]*A.coeff[1][0];
    }
        
    return det;
}

rmat inverse(rmat A){
    rmat invA;
    float detA;
    if (A.rown!=A.coln){
        printf("l'inverse n'est défini que pour les matrices carrées\n");
        exit(1);
    }else {
        detA=det(A);
        if (detA==0){
            printf("la matrices n'est pas inversible\n");
            exit(1);
        }
    }
    invA=init(A.rown, A.coln);
     invA.coeff[0][0] = A.coeff[1][1] / detA;
     invA.coeff[0][1] = -A.coeff[0][1] / detA;
     invA.coeff[1][0] = -A.coeff[1][0] / detA;
     invA.coeff[1][1] = A.coeff[0][0] / detA;
   
    return invA;
}

