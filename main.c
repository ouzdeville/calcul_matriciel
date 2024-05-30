#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"

int main() {
    rmat A, B, C, T, invA;
    int i, j;
    srand(time(NULL));

    A = init(2, 2);
    B = init(2, 2);

    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            A.coeff[i][j] = rand() % 2;
            B.coeff[i][j] = rand() % 2;
        }
    }

    printf("A =\n");
    affiche(A);
    printf("B =\n");
    affiche(B);

    C = mult(A, B);
    printf("C (A * B) =\n");
    affiche(C);
    free(C.coeff);  

    C = add(A, B);
    printf("C (A + B) =\n");
    affiche(C);
    free(C.coeff); 

    T = transposition(A);
    printf("T (transposé de A) =\n");
    affiche(T);
    free(T.coeff); 

    float determinant = det(A);
    printf("det(A) = %0.2f\n", determinant);

    int rank = rang(A);
    printf("rank(A) = %d\n", rank);

    invA = init(A.rown, A.coln);
    int hasInverse = inverse(A, &invA);
    if (hasInverse) {
        printf("inv(A) =\n");
        affiche(invA);
    } else {
        printf("A est singulière et n'a pas d'inverse.\n");
    }
    free(invA.coeff); 

    free(A.coeff);
    free(B.coeff);

    return 0;
}
