#include <stdio.h>
#include <stdlib.h>
#include "realmatrix.h"


int main()
{
    int ligne, colonne;
    printf("Donner le nmbre de lignes");
    scanf("%d",&ligne);
    printf("Donner le nmbre de colonnes");
    scanf("%d",&colonne);
    rmat M=init(ligne,colonne);
    affiche(M);

    // Initialisation des matrices A et B avec des valeurs pour tester
    rmat A = init(2, 2);
    rmat B = init(2, 2);

    A.coeff[0][0] = 1; A.coeff[0][1] = 2;
    A.coeff[1][0] = 3; A.coeff[1][1] = 4;

    B.coeff[0][0] = 5; B.coeff[0][1] = 6;
    B.coeff[1][0] = 7; B.coeff[1][1] = 8;

    // Addition de A et B
    rmat C = add(A, B);
    printf("Matrice C (A + B):\n");
    for (int i = 0; i < C.rown; i++) {
        for (int j = 0; j < C.coln; j++) {
            printf("%.2f ", C.coeff[i][j]);
        }
        printf("\n");
    }

    // Multiplication de A et B
    rmat D = mult(A, B);
    printf("\nMatrice D (A * B):\n");
    for (int i = 0; i < D.rown; i++) {
        for (int j = 0; j < D.coln; j++) {
            printf("%.2f ", D.coeff[i][j]);
        }
        printf("\n");
    }


       // Exemple d'utilisation pour la fontion inverse
    rmat A = init(3, 3); // Création d'une matrice 3x3
    rmat invA; // Matrice pour stocker l'inverse

    // Affichage de la matrice A
    printf("Matrice A :\n");
    affiche(A);

    // Inversion de la matrice A
    if (inverse(A, &invA)) {
        printf("\nMatrice inverse :\n");
        affiche(invA);
    }


    // Calcul du déterminant de la matrice M
    printf("Determinant de la matrice M : %0.2f\n", det(M));

        // Transposition de la matrice M
    rmat transposed_M = transposition(M);
    printf("\nMatrice transposée de M :\n");
    affiche(transposed_M);

    // Libération de la mémoire allouée pour les matrices
    freeMatrix(M);
    freeMatrix(transposed_M);




    
    return 1;
}