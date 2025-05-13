
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

rmat add(rmat A, rmat B) {
    rmat C;
    int i, j;

    // Initialisation de C en fonction des dimensions de A et B
    C.rown = A.rown;
    C.coln = A.coln;

    // Allocation mémoire pour C.coeff
    C.coeff = (float **)malloc(C.rown * sizeof(float *));
    for (i = 0; i < C.rown; i++) {
        C.coeff[i] = (float *)malloc(C.coln * sizeof(float));
    }

    // Vérification de la compatibilité des dimensions
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Erreur : les deux matrices doivent avoir le même nombre de lignes et de colonnes.\n");
        return C;  // Retourne une matrice vide en cas d'erreur
    }

    // Addition des matrices
    for (i = 0; i < C.rown; i++) {
        for (j = 0; j < C.coln; j++) {
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }

    // Affichage des dimensions et du résultat
    printf("La somme des deux matrices vaut : \n");
    

    return C;
}

rmat mult(rmat A, rmat B){
    rmat P;
    int i,j,k;

    P.rown = A.rown;
    P.coln = B.coln;

    
    P.coeff = (float **)malloc(P.rown * sizeof(float *));
    for (i = 0; i < P.rown; i++) {
        P.coeff[i] = (float *)malloc(P.coln * sizeof(float));
    }

    if( A.rown != B.coln ){
        printf("Erreur le nombre de colonne de B doit etre egal au nombre de ligne de A");
    }else{
        // Multiplication des matrices
      for (i = 0; i < P.rown; i++) {
        for (j = 0; j < P.coln; j++) {
            P.coeff[i][j] = 0.0;
            for (k = 0; k < A.coln; k++) {
                P.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
      }

    }
    printf("Le produit des deux matrices vaut : \n");
    return P;
}
rmat transposition(rmat A){
    rmat T;
    int i,j;

    T.rown = A.coln;
    T.coln = A.rown;

    
    T.coeff = (float **)malloc(T.rown * sizeof(float *));
    for (i = 0; i < T.rown; i++) {
        T.coeff[i] = (float *)malloc(T.coln * sizeof(float));
    }
        // transposition d'une matrice
      for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            T.coeff[j][i] = A.coeff[i][j];
        }
      }
    printf("La transposition de A vaut : \n");
    return T;
}
int inverse(rmat A, rmat *invA){
    int i;
     
    if (A.rown != 2 || A.coln != 2) {
        printf("Seules les matrices 2x2 peuvent être inversées dans cette fonction.\n");
        return 0; // Retourne 0 si la matrice n'est pas 2x2
    }
    // Calcul du déterminant pour une matrice 2x2
    float det = A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];

    invA->rown = A.coln;
    invA->coln = A.rown;
    invA->coeff = (float **)malloc(invA->rown * sizeof(float *));
    
    for (i = 0; i < invA->rown; i++) {
        invA->coeff[i] = (float *)malloc(invA->coln * sizeof(float));
    }
    if( det == 0 ){
        printf("A ne possede pas d'inverse");
    }

    invA->coeff[0][0] = A.coeff[1][1] / det;
    invA->coeff[0][1] = -A.coeff[0][1] / det;
    invA->coeff[1][0] = -A.coeff[1][0] / det;
    invA->coeff[1][1] = A.coeff[0][0] / det;    
    printf("L'inverse de A vaut: \n"); 
    return 1;                                                                     
}
float det(rmat A){

    if (A.rown != A.coln) {
        printf("Le déterminant n'est défini que pour les matrices carrées.\n");
        return 0;
    }
    float D = A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
    printf("Le déterminant de A vaut: \n"); 
    return 0;

}
