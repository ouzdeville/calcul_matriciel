#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "realmatrix.h"

rmat init(int ligne, int colonne) 
{
    rmat mat;
    mat.rown = ligne;
    mat.coln = colonne;
    mat.coeff = (float **) malloc(mat.rown * sizeof(float *));
    for (int i = 0; i < mat.rown; i++) {
        mat.coeff[i] = (float *) calloc(mat.coln, sizeof(float));
    }
    return mat;
}

rmat init_Id(int ordre) 
{
    rmat mat = init(ordre, ordre);
    for (int i = 0; i < ordre; i++) {
        mat.coeff[i][i] = 1.0;
    }
    return mat;
}

void affiche(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            printf("%0.2f\t", A.coeff[i][j]);
        }
        printf("\n");
    }
}

rmat add(rmat A, rmat B) {
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Les dimensions des matrices ne correspondent pas pour l'addition\n");
        exit(1);
    }
    rmat C = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }
    return C;
}

rmat mult(rmat A, rmat B) {
    if (A.coln != B.rown) {
        printf("Multiplication de matrices impossible\n");
        exit(1);
    }
    rmat C = init(A.rown, B.coln);
    for (int i = 0; i < C.rown; i++) {
        for (int j = 0; j < C.coln; j++) {
            for (int k = 0; k < A.coln; k++) {
                C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }
    return C;
}

rmat transposition(rmat A) {
    rmat T = init(A.coln, A.rown);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            T.coeff[j][i] = A.coeff[i][j];
        }
    }
    return T;
}

float det(rmat A) {
    if (A.rown != A.coln) {
        printf("La matrice doit être carrée pour calculer le déterminant\n");
        exit(1);
    }
    int n = A.rown;
    float determinant = 0;
    if (n == 1) {
        return A.coeff[0][0];
    } else if (n == 2) {
        return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
    } else {
        for (int k = 0; k < n; k++) {
            rmat submatrix = init(n - 1, n - 1);
            for (int i = 1; i < n; i++) {
                int colIndex = 0;
                for (int j = 0; j < n; j++) {
                    if (j == k) continue;
                    submatrix.coeff[i - 1][colIndex] = A.coeff[i][j];
                    colIndex++;
                }
            }
            determinant += (k % 2 == 0 ? 1 : -1) * A.coeff[0][k] * det(submatrix);
            free_matrix(submatrix);
        }
    }
    return determinant;
}

void free_matrix(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        free(A.coeff[i]);
    }
    free(A.coeff);
}

float trace(rmat A) {
    if (A.rown != A.coln) {
        printf("La matrice doit être carrée pour calculer la trace\n");
        exit(1);
    }
    float trace = 0;
    for (int i = 0; i < A.rown; i++) {
        trace += A.coeff[i][i];
    }
    return trace;
}

// Pivot (élimination de Gauss)
rmat pivot(rmat A) {
    int n = A.rown;
    rmat B = init(n, A.coln);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < A.coln; j++) {
            B.coeff[i][j] = A.coeff[i][j];
        }
    }
    
    for (int k = 0; k < n; k++) {
        // Recherche du pivot
        for (int i = k + 1; i < n; i++) {
            if (B.coeff[k][k] != 0) {
                float factor = B.coeff[i][k] / B.coeff[k][k];
                for (int j = k; j < A.coln; j++) {
                    B.coeff[i][j] -= factor * B.coeff[k][j];
                }
            }
        }
    }
    
    return B;
}

// Calcul du rang de la matrice
int rang(rmat A) {
    rmat B = pivot(A);
    int rang = 0;
    int n = B.rown;
    int m = B.coln;
    for (int i = 0; i < n; i++) {
        int nonZero = 0;
        for (int j = 0; j < m; j++) {
            if (B.coeff[i][j] != 0) {
                nonZero = 1;
                break;
            }
        }
        if (nonZero) {
            rang++;
        }
    }
    free_matrix(B);
    return rang;
}

float* valeurPropre(rmat A) {
    return NULL;
}

int dimEspacePropre(rmat A, float lambda) {
    return 0;
}
