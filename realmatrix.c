#include "realmatrix.h"
#include <stdlib.h>
#include <stdio.h>

rmat init(int ligne, int colonne) {
    rmat mat;
    mat.rown = ligne;
    mat.coln = colonne;
    mat.coeff = (float **)malloc(mat.rown * sizeof(float *));
    for (int i = 0; i < mat.rown; i++) {
        mat.coeff[i] = (float *)calloc(mat.coln, sizeof(float));
    }
    return mat;
}

rmat init_Id(int ordre) {
    rmat mat = init(ordre, ordre);
    for (int i = 0; i < ordre; i++) {
        mat.coeff[i][i] = 1.0;
    }
    return mat;
}

rmat add(rmat A, rmat B) {
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Erreur: les matrices doivent avoir les memes dimensions pour etre additionnees.\n");
        return init(0, 0); // Return an empty matrix on error
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
        printf("Erreur: les dimensions internes doivent etre egales pour la multiplication.\n");
        return init(0, 0); // Return an empty matrix on error
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

void affiche(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            printf("%0.2f\t", A.coeff[i][j]);
        }
        printf("\n");
    }
}

rmat transposition(rmat A) {
    rmat trans = init(A.coln, A.rown);
    for (int i = 0; i < A.coln; i++) {
        for (int j = 0; j < A.rown; j++) {
            trans.coeff[i][j] = A.coeff[j][i];
        }
    }
    return trans;
}

float det(rmat A) {
    if (A.rown != A.coln) {
        printf("Le determinant ne peut etre calcule que pour une matrice carree.\n");
        return 0.0;
    }
    if (A.rown == 1) {
        return A.coeff[0][0];
    }
    if (A.rown == 2) {
        return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
    }
    float determinant = 0.0;
    for (int k = 0; k < A.coln; k++) {
        rmat submatrix = init(A.rown - 1, A.coln - 1);
        for (int i = 1; i < A.rown; i++) {
            int subi = 0;
            for (int j = 0; j < A.coln; j++) {
                if (j == k) continue;
                submatrix.coeff[i - 1][subi++] = A.coeff[i][j];
            }
        }
        determinant += (k % 2 == 0 ? 1 : -1) * A.coeff[0][k] * det(submatrix);
        for (int i = 0; i < submatrix.rown; i++) {
            free(submatrix.coeff[i]);
        }
        free(submatrix.coeff);
    }
    return determinant;
}

int inverse(rmat A, rmat *invA) {
    if (A.rown != A.coln) {
        printf("La matrice doit être carree pour pouvoir etre inversee.\n");
        return 0;
    }

    int n = A.rown;
    rmat identity = init_Id(n);
    rmat temp = init(n, n);

    // Copy A to temp
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp.coeff[i][j] = A.coeff[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        int pivot_row = i;
        while (pivot_row < n && temp.coeff[pivot_row][i] == 0) {
            pivot_row++;
        }
        if (pivot_row == n) {
            printf("La matrice n'est pas inversible.\n");
            for (int i = 0; i < n; i++) {
                free(temp.coeff[i]);
                free(identity.coeff[i]);
            }
            free(temp.coeff);
            free(identity.coeff);
            return 0;
        }

        if (pivot_row != i) {
            float *temp_row = temp.coeff[i];
            temp.coeff[i] = temp.coeff[pivot_row];
            temp.coeff[pivot_row] = temp_row;

            float *identity_row = identity.coeff[i];
            identity.coeff[i] = identity.coeff[pivot_row];
            identity.coeff[pivot_row] = identity_row;
        }

        float pivot = temp.coeff[i][i];
        for (int j = 0; j < n; j++) {
            temp.coeff[i][j] /= pivot;
            identity.coeff[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                float factor = temp.coeff[k][i];
                for (int j = 0; j < n; j++) {
                    temp.coeff[k][j] -= factor * temp.coeff[i][j];
                    identity.coeff[k][j] -= factor * identity.coeff[i][j];
                }
            }
        }
    }

    *invA = identity;

    for (int i = 0; i < n; i++) {
        free(temp.coeff[i]);
    }
    free(temp.coeff);

    return 1;
}
