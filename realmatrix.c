#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "realmatrix.h"

rmat init(int ligne, int colonne){
    rmat mat;
    mat.rown = ligne;
    mat.coln = colonne;
    mat.coeff = (float **) malloc(mat.rown * sizeof(float *));
    for (int i = 0; i < mat.rown; i++){
        mat.coeff[i] = (float *) calloc(mat.coln, sizeof(float));
    }
    return mat;
}

rmat init_Id(int ordre){
    rmat mat = init(ordre, ordre);
    for (int i = 0; i < mat.rown; i++){
        mat.coeff[i][i] = 1;
    }
    return mat;
}

void affiche(rmat A){
    for (int i = 0; i < A.rown; i++){
        for (int j = 0; j < A.coln; j++){
            printf("%0.2f \t", A.coeff[i][j]);
        }
        printf("\n");
    }
}

rmat add(rmat A, rmat B){
    rmat C = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++){
        for (int j = 0; j < A.coln; j++){
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }
    return C;
}

rmat mult(rmat A, rmat B){
    rmat C = init(A.rown, B.coln);
    for (int i = 0; i < C.rown; i++){
        for (int j = 0; j < C.coln; j++){
            for (int k = 0; k < A.coln; k++){
                C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }
    return C;
}

rmat transposition(rmat A){
    rmat T = init(A.coln, A.rown);
    for (int i = 0; i < A.rown; i++){
        for (int j = 0; j < A.coln; j++){
            T.coeff[j][i] = A.coeff[i][j];
        }
    }
    return T;
}

float det(rmat A){
    if (A.rown != A.coln) return 0; 

    int n = A.rown;
    rmat tmp = init(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tmp.coeff[i][j] = A.coeff[i][j];

    float determinant = 1;
    for (int i = 0; i < n; i++){
        if (tmp.coeff[i][i] == 0){
            int swapRow = i + 1;
            while (swapRow < n && tmp.coeff[swapRow][i] == 0)
                swapRow++;
            if (swapRow == n) {
                free(tmp.coeff); 
                return 0; 
            }
            float *temp = tmp.coeff[i];
            tmp.coeff[i] = tmp.coeff[swapRow];
            tmp.coeff[swapRow] = temp;
            determinant = -determinant;
        }
        determinant *= tmp.coeff[i][i];
        for (int j = i + 1; j < n; j++){
            float factor = tmp.coeff[j][i] / tmp.coeff[i][i];
            for (int k = i; k < n; k++){
                tmp.coeff[j][k] -= factor * tmp.coeff[i][k];
            }
        }
    }
    for (int i = 0; i < n; i++)
        free(tmp.coeff[i]); 
    free(tmp.coeff); 
    return determinant;
}

rmat pivot(rmat A){
    rmat P = init(A.rown, A.coln);
    rmat I = init_Id(A.rown);
    for (int i = 0; i < A.rown; i++){
        int max = i;
        for (int j = i + 1; j < A.rown; j++){
            if (fabs(A.coeff[j][i]) > fabs(A.coeff[max][i])){
                max = j;
            }
        }
        if (max != i){
            float *temp = I.coeff[i];
            I.coeff[i] = I.coeff[max];
            I.coeff[max] = temp;
        }
    }
    for (int i = 0; i < A.rown; i++){
        for (int j = 0; j < A.coln; j++){
            P.coeff[i][j] = I.coeff[i][j];
        }
    }
    for (int i = 0; i < A.rown; i++)
        free(I.coeff[i]); 
    free(I.coeff);
    return P;
}

int rang(rmat A){
    int rank = 0;
    rmat tmp = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++)
        for (int j = 0; j < A.coln; j++)
            tmp.coeff[i][j] = A.coeff[i][j];

    for (int row = 0; row < A.rown; row++){
        int lead = -1;
        for (int col = 0; col < A.coln; col++){
            if (fabs(tmp.coeff[row][col]) > 1e-10){
                lead = col;
                break;
            }
        }
        if (lead != -1){
            rank++;
            for (int i = row + 1; i < A.rown; i++){
                float factor = tmp.coeff[i][lead] / tmp.coeff[row][lead];
                for (int j = lead; j < A.coln; j++){
                    tmp.coeff[i][j] -= factor * tmp.coeff[row][j];
                }
            }
        }
    }
    for (int i = 0; i < A.rown; i++)
        free(tmp.coeff[i]); 
    free(tmp.coeff);
    return rank;
}

int inverse(rmat A, rmat *invA) {
    if (A.rown != A.coln) return 0; 

    int n = A.rown;
    rmat tmp = init(n, 2 * n);
    *invA = init_Id(n); 

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tmp.coeff[i][j] = A.coeff[i][j];
            tmp.coeff[i][j + n] = (*invA).coeff[i][j]; 
        }
    }

    for (int i = 0; i < n; i++) {
        if (fabs(tmp.coeff[i][i]) < 1e-10) {
            int swapRow = i + 1;
            while (swapRow < n && fabs(tmp.coeff[swapRow][i]) < 1e-10)
                swapRow++;
            if (swapRow == n) {
                for (int k = 0; k < n; k++)
                    free(tmp.coeff[k]); 
                free(tmp.coeff);
                return 0; 
            }
            float *temp = tmp.coeff[i];
            tmp.coeff[i] = tmp.coeff[swapRow];
            tmp.coeff[swapRow] = temp;
        }
        float diag = tmp.coeff[i][i];
        if (fabs(diag) < 1e-10) {
            for (int k = 0; k < n; k++)
                free(tmp.coeff[k]); 
            free(tmp.coeff);
            return 0; 
        }
        for (int j = 0; j < 2 * n; j++) {
            tmp.coeff[i][j] /= diag;
        }
        for (int j = 0; j < n; j++) {
            if (j != i) {
                float factor = tmp.coeff[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    tmp.coeff[j][k] -= factor * tmp.coeff[i][k];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            (*invA).coeff[i][j] = tmp.coeff[i][j + n]; 
        }
    }
    for (int i = 0; i < n; i++)
        free(tmp.coeff[i]); 
    free(tmp.coeff); 
    return 1;
}
