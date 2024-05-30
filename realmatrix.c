#include <stdio.h>
#include <stdlib.h>
#include "realmatrix.h"

//Fonction init
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

//Fonction init_ID
rmat init_Id(int ordre) {
    rmat mat;
    mat.rown = ordre;
    mat.coln = ordre;
    mat.coeff = (float **)malloc(mat.rown * sizeof(float *));
    for (int i = 0; i < mat.rown; i++) {
        mat.coeff[i] = (float *)malloc(mat.coln * sizeof(float));
        for (int j = 0; j < mat.coln; j++) {
            if (i == j) {
                mat.coeff[i][j] = 1.0;
            } else {
                mat.coeff[i][j] = 0.0;
            }
        }
    }
    return mat;
}

//Fonction affiche
void affiche(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            printf("%0.2f \t", A.coeff[i][j]);
        }
        printf("\n");
    }
}

//Fonction transposition
rmat transposition(rmat A) {
    rmat trans;
    trans.rown = A.coln;
    trans.coln = A.rown;
    trans.coeff = (float **)malloc(trans.rown * sizeof(float *));
    for (int i = 0; i < trans.rown; i++) {
        trans.coeff[i] = (float *)malloc(trans.coln * sizeof(float));
        for (int j = 0; j < trans.coln; j++) {
            trans.coeff[i][j] = A.coeff[j][i];
        }
    }
    return trans;
}

//Fonction addition 
rmat add(rmat A, rmat B) {
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Les matrices doivent avoir les memes dimensions pour être additionnees.\n");
        rmat empty;
        empty.rown = 0;
        empty.coln = 0;
        empty.coeff = NULL;
        return empty;
    }

    rmat result = init(A.rown, A.coln);

    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            result.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }

    return result;
}

//Fonction multiplication
rmat mult(rmat A, rmat B) {
    // Vérification des dimensions pour la multiplication
    if (A.coln != B.rown) {
        // printf("Les matrices doivent avoir les memes dimensions pour etre multipliees.\n");
        rmat empty;
        empty.rown = 0;
        empty.coln = 0;
        empty.coeff = NULL;
        return empty;
    }

    // Création de la matrice résultante
    rmat result;
    result.rown = A.rown;
    result.coln = B.coln;
    result.coeff = (float **)malloc(result.rown * sizeof(float *));
    for (int i = 0; i < result.rown; i++) {
        result.coeff[i] = (float *)calloc(result.coln, sizeof(float));
    }

    // Multiplication des matrices
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < B.coln; j++) {
            for (int k = 0; k < A.coln; k++) {
                result.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }

    return result;
}

//Fonction determinant
float det(rmat A) {
    if (A.rown != A.coln) {
        printf("Le determinant ne peut etre calculer que pour une matrice carree.\n");
        return 0.0;
    }
    if (A.rown == 1) {
        return A.coeff[0][0];
    }
    float determinant = 0.0;
    rmat submatrix;
    submatrix.rown = A.rown - 1;
    submatrix.coln = A.coln - 1;
    submatrix.coeff = (float **)malloc(submatrix.rown * sizeof(float *));
    for (int i = 0; i < submatrix.rown; i++) {
        submatrix.coeff[i] = (float *)malloc(submatrix.coln * sizeof(float));
    }
    int sign = 1;
    for (int j = 0; j < A.coln; j++) {
        int subi = 0;
        for (int row = 1; row < A.rown; row++) {
            int subj = 0;
            for (int col = 0; col < A.coln; col++) {
                if (col == j) {
                    continue;
                }
                submatrix.coeff[subi][subj] = A.coeff[row][col];
                subj++;
            }
            subi++;
        }
        determinant += sign * A.coeff[0][j] * det(submatrix);
        sign = -sign;
    }
    for (int i = 0; i < submatrix.rown; i++) {
        free(submatrix.coeff[i]);
    }
    free(submatrix.coeff);
    return determinant;
}

//Fonction inverse
int inverse(rmat A, rmat *invA) {
    // Vérification que A est carrée
    if (A.rown != A.coln) {
        printf("La matrice doit etre carree pour pouvoir etre inversee.\n");
        return 0;
    }

    // Création de la matrice identité de même taille que A
    rmat identity = init_Id(A.rown);

    // Copie de la matrice A dans une nouvelle matrice temporaire
    rmat temp = A;

    // Application de la méthode de Gauss-Jordan
    for (int i = 0; i < temp.rown; i++) {
        // Recherche de la première rangée avec un pivot non nul
        int pivot_row = i;
        while (pivot_row < temp.rown && temp.coeff[pivot_row][i] == 0) {
            pivot_row++;
        }
        if (pivot_row == temp.rown) {
            // printf("La matrice n est pas inversible.\n");
            return 0;
        }

        // Échange des lignes pour avoir le pivot en position (i, i)
        if (pivot_row != i) {
            float *temp_row = temp.coeff[i];
            temp.coeff[i] = temp.coeff[pivot_row];
            temp.coeff[pivot_row] = temp_row;

            float *identity_row = identity.coeff[i];
            identity.coeff[i] = identity.coeff[pivot_row];
            identity.coeff[pivot_row] = identity_row;
        }

        // Division de la ligne par le pivot pour avoir 1 sur la diagonale
        float pivot = temp.coeff[i][i];
        for (int j = 0; j < temp.coln; j++) {
            temp.coeff[i][j] /= pivot;
            identity.coeff[i][j] /= pivot;
        }

        // Élimination des autres éléments dans la colonne
        for (int k = 0; k < temp.rown; k++) {
            if (k != i) {
                float factor = temp.coeff[k][i];
                for (int j = 0; j < temp.coln; j++) {
                    temp.coeff[k][j] -= factor * temp.coeff[i][j];
                    identity.coeff[k][j] -= factor * identity.coeff[i][j];
                }
            }
        }
    }

    // Copie du résultat dans la matrice inverse
    *invA = identity;

    return 1;
}

// Fonction pivot
rmat pivot(rmat A){
    int i = 0, j = 0, k = 0, n = A.rown, m = A.coln;
    while (i < n && j < m) {
        int maxi = i;
        for (k = i + 1; k < n; k++) {
            if (abs(A.coeff[k][j]) > abs(A.coeff[maxi][j])) {
                maxi = k;
            }
        }
        if (A.coeff[maxi][j] != 0) {
            float *temp = A.coeff[i];
            A.coeff[i] = A.coeff[maxi];
            A.coeff[maxi] = temp;
            for (k = i + 1; k < n; k++) {
                float factor = A.coeff[k][j] / A.coeff[i][j];
                for (int l = j; l < m; l++) {
                    A.coeff[k][l] -= A.coeff[i][l] * factor;
                }
            }
            i++;
        }
        j++;
    }
    return A;
}

// Fonction rang
int rang(rmat A){
    int i = 0, j = 0, n = A.rown, m = A.coln, rank = 0;
    while (i < n && j < m) {
        if (A.coeff[i][j] != 0) {
            rank++;
            i++;
        } else {
            j++;
        }
    }
    return rank;
}


