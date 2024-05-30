#include <stdio.h>
#include <stdlib.h>
#include "realmatrix.h"

int main() {
    int ligne, colonne;

    printf("Donner le nombre de lignes : ");
    scanf("%d", &ligne);
    printf("Donner le nombre de colonnes : ");
    scanf("%d", &colonne);

    rmat M = init(ligne, colonne);

    // Demandez à l'utilisateur de saisir les valeurs de la matrice M
    printf("Remplissez la matrice M :\n");
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("M[%d][%d] : ", i, j);
            scanf("%f", &M.coeff[i][j]);
        }
    }

    printf("Matrice M :\n");
    affiche(M);

    printf("Entrez une autre matrice N pour l'addition (memes dimensions que M) :\n");
    rmat N = init(ligne, colonne);
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            printf("N[%d][%d] : ", i, j);
            scanf("%f", &N.coeff[i][j]);
        }
    }

    printf("Somme de M et N :\n");
    rmat sum = add(M, N);
    affiche(sum);

    printf("Entrez une autre matrice P pour la multiplication (nombre de colonnes de la 2e matrice doit etre egal au nombre de lignes de M) :\n");
    int col_P;
    printf("Donner le nombre de colonnes de la matrice pour multiplication : ");
    scanf("%d", &col_P);

    rmat P = init(colonne, col_P); // Adjust the dimensions accordingly
    for (int i = 0; i < colonne; i++) {
        for (int j = 0; j < col_P; j++) {
            printf("P[%d][%d] : ", i, j);
            scanf("%f", &P.coeff[i][j]);
        }
    }

    printf("Produit de M et P :\n");
    rmat product = mult(M, P);
    affiche(product);

    rmat transM = transposition(M);
    printf("Matrice transposee de M :\n");
    affiche(transM);

    float determinant_M = det(M);
    printf("Determinant de M : %0.6f\n", determinant_M);

    rmat inv_M;
    int success = inverse(M, &inv_M);
    if (success) {
        printf("Inverse de M :\n");
        affiche(inv_M);
        free(inv_M.coeff);
    } else {
        printf("La matrice M n'est pas inversible.\n");
    }

    free(M.coeff);
    free(N.coeff);
    free(P.coeff);
    free(sum.coeff);
    free(product.coeff);
    free(transM.coeff);

    return 0;
}
