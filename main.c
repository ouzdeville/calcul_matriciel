#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"

int main() {
    rmat A, B, C, T, invA;
    int i, j;
    srand(time(NULL));

    // Initialiser les matrices A et B avec des valeurs aleatoires
    A = init(2, 2);
    B = init(2, 2);

    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            A.coeff[i][j] = ((int)rand()) % 2;
            B.coeff[i][j] = ((int)rand()) % 2;
        }
    }

    //Afficher les matrices A et B
    printf("A =\n");
    affiche(A);
    printf("B =\n");
    affiche(B);

    // Multiplication de matrices
    C = mult(A, B);
    printf("C (A * B) =\n");
    affiche(C);

    // Addition de matrices
    C = add(A, B);
    printf("C (A + B) =\n");
    affiche(C);

    // Transposition de matrices
    T = transposition(A);
    printf("T (transpose de A) =\n");
    affiche(T);

    // Determinant de A
    float determinant = det(A);
    printf("det(A) = %0.2f\n", determinant);

    // Rang de A
    int rank = rang(A);
    printf("rank(A) = %d\n", rank);

    // Inverse de A
    invA = init(A.rown, A.coln);
    int hasInverse = inverse(A, &invA);
    if (hasInverse) {
        printf("inv(A) =\n");
        affiche(invA);
    } else {
        printf("A est singuliere et n'a pas d'inverse.\n");
    }

    // Liberer la memoire allouee
    free(A.coeff);
    free(B.coeff);
    free(C.coeff);
    free(T.coeff);
    free(invA.coeff);

    return 0;
}
