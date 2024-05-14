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