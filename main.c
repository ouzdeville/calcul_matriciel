#include <stdio.h>
#include <stdlib.h>
#include "realmatrix.h"

int main() {
    int ligneA, colonneA, ligneB, colonneB;

    printf("Donner le nombre de lignes de la matrice A : ");
    scanf("%d", &ligneA);
    printf("Donner le nombre de colonnes de la matrice A : ");
    scanf("%d", &colonneA);

    printf("Donner le nombre de lignes de la matrice B : ");
    scanf("%d", &ligneB);
    printf("Donner le nombre de colonnes de la matrice B : ");
    scanf("%d", &colonneB);

    rmat A = init(ligneA, colonneA);
    rmat B = init(ligneB, colonneB);

    printf("Remplissez la matrice A :\n");
    for (int i = 0; i < ligneA; i++) {
        for (int j = 0; j < colonneA; j++) {
            printf("A[%d][%d] : ", i, j);
            scanf("%f", &A.coeff[i][j]);
        }
    }

    printf("Remplissez la matrice B :\n");
    for (int i = 0; i < ligneB; i++) {
        for (int j = 0; j < colonneB; j++) {
            printf("B[%d][%d] : ", i, j);
            scanf("%f", &B.coeff[i][j]);
        }
    }

    printf("\nMatrice A :\n");
    affiche(A);
    printf("\nMatrice B :\n");
    affiche(B);

    printf("\nPivot de A :\n");
    rmat pivotA = pivot(A);
    affiche(pivotA);
    printf("\nRang de A : %d\n", rang(A));

    printf("\nPivot de B :\n");
    rmat pivotB = pivot(B);
    affiche(pivotB);
    printf("\nRang de B : %d\n", rang(B));

    printf("\nAddition de A et B :\n");
    rmat sumAB = add(A, B);
    affiche(sumAB);

    printf("\nProduit de A et B :\n");
    rmat prodAB = mult(A, B);
    if (prodAB.coeff != NULL) {
        affiche(prodAB);
    } else {
        printf("Impossible de multiplier les matrices. Les dimensions ne sont pas valides.\n");
    }

    printf("\nInverse de A :\n");
    rmat invA;
    int successA = inverse(A, &invA);
    if (successA) {
        affiche(invA);
        printf("\nDeterminant de A : %0.2f\n", det(A));
        printf("\nTransposee de A :\n");
        rmat transA = transposition(A);
        affiche(transA);
    } else {
        printf("La matrice A n'est pas inversible.\n");
    }

    printf("\nInverse de B :\n");
    rmat invB;
    int successB = inverse(B, &invB);
    if (successB) {
        affiche(invB);
        printf("\nDeterminant de B : %0.2f\n", det(B));
        printf("\nTransposee de B :\n");
        rmat transB = transposition(B);
        affiche(transB);
    } else {
        printf("La matrice B n'est pas inversible.\n");
    }

    // Libération de la mémoire
    free(A.coeff);
    free(B.coeff);
    if (successA) {
        free(invA.coeff);
    }
    if (successB) {
        free(invB.coeff);
    }

    return 0;
}
