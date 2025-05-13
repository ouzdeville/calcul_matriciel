#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "realmatrix.h"

int main() {
    rmat A, B, C;
    A = init(2, 2);
    B = init(2, 2);
    int i, j;
    srand(time(NULL));

    // Remplissage aléatoire
    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            A.coeff[i][j] = rand() % 6;
            B.coeff[i][j] = rand() % 6;
        }
    }

    printf("Matrice A :\n");
    affiche(A);
    printf("Matrice B :\n");
    affiche(B);

    // Menu utilisateur
    char choix[20];
    printf("Quelle opération voulez-vous effectuer ?\n");
    printf("Options : add / mult / transpose / det / inverse\n");
    printf("Votre choix : ");
    scanf("%s", choix);

    if (strcmp(choix, "add") == 0) {
        C = add(A, B);
        printf("Résultat A + B :\n");
        affiche(C);
    } else if (strcmp(choix, "mult") == 0) {
        C = mult(A, B);
        printf("Résultat A * B :\n");
        affiche(C);
    } else if (strcmp(choix, "transpose") == 0) {
        rmat At = transposition(A);
        printf("Transposee de A :\n");
        affiche(At);
        // Libération mémoire
        for (i = 0; i < At.rown; i++) free(At.coeff[i]);
        free(At.coeff);
    } else if (strcmp(choix, "det") == 0) {
        float determinant = det(A);
        printf("Déterminant de A : %.2f\n", determinant);
    } else if (strcmp(choix, "inverse") == 0) {
        rmat invA = init(A.rown, A.coln);
        if (inverse(A, invA)) {
            printf("Inverse de A :\n");
            affiche(invA);
        } else {
            printf("Inverse impossible.\n");
        }
        for (i = 0; i < invA.rown; i++) free(invA.coeff[i]);
        free(invA.coeff);
    } else {
        printf("Option non reconnue.\n");
    }

    // Libération mémoire des matrices principales
    for (i = 0; i < A.rown; i++) {
        free(A.coeff[i]);
        free(B.coeff[i]);
    }
    free(A.coeff);
    free(B.coeff);

    if (strcmp(choix, "add") == 0 || strcmp(choix, "mult") == 0) {
        for (i = 0; i < C.rown; i++) free(C.coeff[i]);
        free(C.coeff);
    }

    return 0;
}
