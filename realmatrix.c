#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"

rmat init(int ligne, int colonne) {
    rmat mat;
    mat.rown = ligne;
    mat.coln = colonne;
    mat.coeff = (float **)malloc(mat.rown * sizeof(float *));
    for (int i = 0; i < mat.rown; i++) {
        mat.coeff[i] = calloc(mat.coln, sizeof(float));
    }
    return mat;
}

void affiche(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            printf("%0.2f \t", A.coeff[i][j]);
        }
        printf("\n");
    }
}

rmat init_Id(int ordre) {
    rmat mat = init(ordre, ordre);
    for (int i = 0; i < ordre; i++) {
        mat.coeff[i][i] = 1;
    }
    return mat;
}

rmat add(rmat A, rmat B) {
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Erreur: Les matrices doivent avoir les mêmes dimensions pour l'addition.\n");
        exit(EXIT_FAILURE);
    }
    rmat result = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            result.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }
    return result;
}

rmat mult(rmat A, rmat B) {
    if (A.coln != B.rown) {
        printf("Erreur: Le nombre de colonnes de la première matrice doit être égal au nombre de lignes de la deuxième matrice pour la multiplication.\n");
        exit(EXIT_FAILURE);
    }
    rmat result = init(A.rown, B.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < B.coln; j++) {
            result.coeff[i][j] = 0;
            for (int k = 0; k < A.coln; k++) {
                result.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }
    return result;
}

rmat transposition(rmat A) {
    rmat result = init(A.coln, A.rown);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            result.coeff[j][i] = A.coeff[i][j];
        }
    }
    return result;
}

int inverse(rmat A, rmat invA) {
    // Implementation du calcul de l'inverse (à compléter)
    return 0;
}

float det(rmat A) {
    // Implementation du calcul du déterminant (à compléter)
    return 0.0;
}

float trace(rmat A) {
    float sum = 0.0;
    for (int i = 0; i < A.rown && i < A.coln; i++) {
        sum += A.coeff[i][i];
    }
    return sum;
}

rmat pivot(rmat A) {
    // Implementation du pivotement (à compléter)
    return A;
}

int rang(rmat A) {
    // Implementation du calcul du rang (à compléter)
    return 0;
}

float *valeurPropre(rmat A) {
    // Implementation du calcul des valeurs propres (à compléter)
    return NULL;
}

int dimEspacePropre(rmat A, float lamda) {
    // Implementation du calcul de la dimension de l'espace propre (à compléter)
    return 0;
}
