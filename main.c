#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"

int main()
{
    rmat A, B, C, invA;
    A = init(2, 2);
    B = init(2, 2);
    int i, j;

    srand(time(NULL));
    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            A.coeff[i][j] = ((int)rand()) % 2;
            B.coeff[i][j] = ((int)rand()) % 2;
        }
    }

    printf("A =\n");
    affiche(A);

    printf("B =\n");
    affiche(B);

    printf("A + B =\n");
    C = add(A, B);
    affiche(C);

    printf("A * B =\n");
    C = mult(A, B);
    affiche(C);

    printf("Transposée de A =\n");
    C = transposition(A);
    affiche(C);

    // Allocation vide, mais ce n’est plus indispensable
    // car inverse() écrase le contenu avec init_Id()
    if (inverse(A, &invA)) {
        printf("Inverse de A :\n");
        affiche(invA);
    } else {
        printf("La matrice A n'est pas inversible.\n");
    }

    return 0;
}
