#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"


int main()
{
    rmat A, B, C;
    A = init(2, 2);
    B = init(2, 2);
    int i, j;
    srand(time(NULL));
    for (i = 0; i < A.rown; i++)
    {
        for (j = 0; j < A.coln; j++)
        {
            A.coeff[i][j] = ((int)rand()) % 2;
            B.coeff[i][j] = ((int)rand()) % 2;
        }
    }

    
    // Afficher les matrices A et B
    printf("Matrice A :\n");
    affiche(A);
    printf("\nMatrice B :\n");
    affiche(B);

    // Addition des matrices A et B
    printf("\nAddition des matrices A et B :\n");
    C = add(A, B);
    affiche(C);

    // Multiplication des matrices A et B
    printf("\nMultiplication des matrices A et B :\n");
    C = mult(A, B);
    affiche(C);

    // Transposition de la matrice A
    printf("\nTransposition de la matrice A :\n");
    C = transposition(A);
    affiche(C);

    // Calcul du déterminant de la matrice A
    printf("\nDeterminant de la matrice A : %f\n", determinant(A));

    // Calcul du rang de la matrice A
    printf("\nRang de la matrice A : %d\n", rang(A));

    // Calcul de l'inverse de la matrice A
    printf("\nInverse de la matrice A :\n");
    if (inverse(A, &C)) {
        affiche(C);
    } else {
        printf("La matrice A n'est pas inversible.\n");
    }

    // Libérer la mémoire
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);

    return 0;
}
