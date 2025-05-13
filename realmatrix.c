#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"


rmat init(int ligne, int colonne) {
    rmat mat;
    mat.rown = ligne;
    mat.coln = colonne;
    mat.coeff = (float **) malloc(mat.rown * sizeof(float *));
    for (int i = 0; i < mat.rown; i++) {
        mat.coeff[i] = calloc(mat.coln, sizeof(float));
    }
    return mat;
}

rmat init_Id(int ordre) {
    rmat mat = init(ordre, ordre);
    for (int i = 0; i < ordre; i++) {
        mat.coeff[i][i] = 1;
    }
    return mat;
}

// Affichage d'une matrice
void affiche(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            printf("%0.2f\t", A.coeff[i][j]);
        }
        printf("\n");
    }
}

// Addition de deux matrices
rmat add(rmat A, rmat B) {
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Erreur : dimensions incompatibles pour l'addition\n");
        return init(0, 0);
    }
    rmat C = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }
    return C;
}

// Multiplication de deux matrices
rmat mult(rmat A, rmat B) {
    if (A.coln != B.rown) {
        printf("Erreur : dimensions incompatibles pour la multiplication\n");
        return init(0, 0);
    }
    rmat C = init(A.rown, B.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < B.coln; j++) {
            for (int k = 0; k < A.coln; k++) {
                C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }
    return C;
}

// Transposition d'une matrice
rmat transposition(rmat A) {
    rmat T = init(A.coln, A.rown);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            T.coeff[j][i] = A.coeff[i][j];
        }
    }
    return T;
}

// Inversion d'une matrice carrée
int inverse(rmat A, rmat *invA){
    if (A.rown != A.coln) {
        printf("Erreur : matrice non carrée\n");
        return 0;
    }

    int n = A.rown;
    *invA = init_Id(n);

    rmat temp = init(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp.coeff[i][j] = A.coeff[i][j];

    for (int i = 0; i < n; i++) {
        if (temp.coeff[i][i] == 0) {
            int j = i + 1;
            while (j < n && temp.coeff[j][i] == 0) j++;
            if (j == n) {
                printf("Erreur : matrice singulière\n");
                return 0;
            }
            float* tmp = temp.coeff[i];
            temp.coeff[i] = temp.coeff[j];
            temp.coeff[j] = tmp;

            tmp = invA->coeff[i];
            invA->coeff[i] = invA->coeff[j];
            invA->coeff[j] = tmp;

        }

        float pivot = temp.coeff[i][i];
        for (int j = 0; j < n; j++) {
            temp.coeff[i][j] /= pivot;
            invA->coeff[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                float factor = temp.coeff[k][i];
                for (int j = 0; j < n; j++) {
                    temp.coeff[k][j] -= factor * temp.coeff[i][j];
                    invA->coeff[k][j] -= factor * invA->coeff[i][j];
                }
            }
        }
    }

    return 1;
}


