#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "realmatrix.h"
// gcc main.c realmatrix.c -o main

int main()
{
    int rowMat1, colMat1, rowMat2, colMat2;
    printf("Entrez le nombre de lignes de la premiere matrice : ");
    do{
        scanf("%d", &rowMat1);
    } while (rowMat1<=0);

    printf("Entrez le nombre de colonnes premiere matrice : ");
    do{
        scanf("%d", &colMat1);
    } while (colMat1<=0);

    printf("\nEntrez le nombre de lignes seconde matrice : ");
    do{
        scanf("%d", &rowMat2);
    } while (rowMat2<=0);

    printf("Entrez le nombre de colonnes seconde matrice : ");
    do{
        scanf("%d", &colMat2);
    } while (colMat2<=0);
    
    // Initialisation des matrices
    rmat A = init(rowMat1, colMat1);
    rmat B = init(rowMat2, colMat2);

    for(int i=0 ; i<rowMat1 ; i++){
        for(int j=0 ; j<colMat1 ; j++){
            A.coeff[i][j] = rand()%10;
        }
    }

    for(int i=0 ; i<rowMat2 ; i++){
        for(int j=0 ; j<colMat2 ; j++){
            B.coeff[i][j] = rand()%10;
        }
    }

    // Affichage des matrices
    printf("\nMatrice A :\n");
    affiche(A);

    printf("\nMatrice B :\n");
    affiche(B);
    printf("\n");

    // Addition des matrices
    rmat C = add(A, B);
    printf("Matrice C (A + B) :\n");
    affiche(C);
    printf("\n");

    // Multiplication des matrices
    rmat D = mult(A, B);
    printf("Matrice D (A * B) :\n");
    affiche(D);
    printf("\n");

    // Calcul du déterminant de A
    float determinantA = det(A);
    printf("Determinant de A: %0.2f\n\n", determinantA);

    // Calcul de l'inverse de A
    rmat invA = init(rowMat1, colMat1);
    if (inverse(A, invA)) {
        printf("Inverse de A :\n");
        affiche(invA);
    } else {
        printf("La matrice A est singuliere et n'a pas d'inverse.\n");
    }
    printf("\n");

    // Calcul du pivot de A
    rmat pivotA = pivot(A);
    printf("Pivot de A :\n");
    affiche(pivotA);
    printf("\n");

    rmat transA = transposition(A);
    printf("\nTransposition de A :\n");
    affiche(transA);
    printf("\n");

    // Calcul du rang de A
    int rangA = rang(A);
    printf("Rang de A : %d\n", rangA);

    // Libération de la mémoire allouée
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(invA);
    free_matrix(pivotA);

    return 0;
}