#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "realmatrix.h"

void remplir_matrice(rmat mat, float valeur) {
    for (int i = 0; i < mat.rown; i++) {
        for (int j = 0; j < mat.coln; j++) {
            mat.coeff[i][j] = valeur;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Usage: %s <commande> -l <ligne> -n <colonne> [options]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int ligne = 0, colonne = 0;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            ligne = atoi(argv[i + 1]);
        } else if (strcmp(argv[i], "-n") == 0) {
            colonne = atoi(argv[i + 1]);
        }
    }

    if (ligne <= 0 || colonne <= 0) {
        printf("Erreur: Les dimensions de la matrice doivent être des entiers positifs.\n");
        return EXIT_FAILURE;
    }

    rmat A, B, C;
    if (strcmp(argv[1], "-init") == 0) {
        A = init(ligne, colonne);
        printf("Matrice initialisée:\n");
        affiche(A);
    } else if (strcmp(argv[1], "-init_Id") == 0) {
        A = init_Id(ligne);
        printf("Matrice identité initialisée:\n");
        affiche(A);
    } else if (strcmp(argv[1], "-add") == 0) {
        A = init(ligne, colonne);
        B = init(ligne, colonne);
        remplir_matrice(A, 1.0); // Remplir A avec des 1 pour test
        remplir_matrice(B, 2.0); // Remplir B avec des 2 pour test
        C = add(A, B);
        printf("Résultat de l'addition:\n");
        affiche(C);
    } else if (strcmp(argv[1], "-mult") == 0) {
        A = init(ligne, colonne);
        B = init(colonne, ligne);
        remplir_matrice(A, 1.0); // Remplir A avec des 1 pour test
        remplir_matrice(B, 2.0); // Remplir B avec des 2 pour test
        C = mult(A, B);
        printf("Résultat de la multiplication:\n");
        affiche(C);
    } else if (strcmp(argv[1], "-tr") == 0) {
        A = init(ligne, colonne);
        remplir_matrice(A, 1.0); // Remplir A avec des 1 pour test
        float tr = trace(A);
        printf("Trace de la matrice: %0.2f\n", tr);
    } else {
        printf("Commande non reconnue.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
