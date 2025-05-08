
#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"



rmat init(int ligne, int colonne){

    rmat mat;
    int i=0;
    mat.rown=ligne;
    mat.coln=colonne;
    // je déclare un tableau cotenant des tableaux (float *)
    // les lignes sont des tablaux de tablaux
    mat.coeff=(float **) malloc(mat.rown *sizeof(float *));
    for ( i = 0; i < mat.rown; i++)
    {
        // chaque ligne est un tableau de réel
        mat.coeff[i]= calloc(mat.coln, sizeof(float));
    }

    return mat;
}

rmat init_Id(int ordre){
    rmat mat;
    int i=0;
    mat=init(ordre, ordre);
     for ( i = 0; i < mat.rown; i++)
    {
        // chaque ligne est un tableau de réel
        mat.coeff[i][i]=1;
    }
    return mat;
}

void affiche(rmat A){
    int i,j;
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            printf("%0.2f \t", A.coeff[i][j]);
        }
        printf("\n");
        
    }
}
//addition
rmat add(rmat A, rmat B) {
    rmatC=init( A.rown , a.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            C.coeff[i][j]=A.coeff[i][j] + B.coeff[i][j];



}
}
return C;

}
//multiplication
rmat mult(rmat A, rmat B){
    rmat C = init(A.rown, B.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < B.coln; j++) {
            for (int k = 0; k < A.coln; k++) {
                C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
}
}
return C;
    }
}
//transposition
rmat transposition(rmat A){
    rmat C = init(A.coln, A.roan);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            C.coeff[j][i] = A.coeff[i][j];
            }
        }
        return  c;
    }
        //inverse
        int inverse(rmat A, rmat invA){
            void inverse_matrix(float mat[N][N], float inv[N][N]) {
                int i, j, k;
                float temp;
            
                // Création de la matrice identité
                for (i = 0; i < N; i++) {
                    for (j = 0; j < N; j++) {
                        inv[i][j] = (i == j) ? 1.0 : 0.0;
                    }
                }
                // Appliquer la méthode de Gauss-Jordan
    for (i = 0; i < N; i++) {
        temp = mat[i][i];
        for (j = 0; j < N; j++) {
            mat[i][j] /= temp;
            inv[i][j] /= temp;
        }
        for (k = 0; k < N; k++) {
            if (k != i) {
                temp = mat[k][i];
                for (j = 0; j < N; j++) {
                    mat[k][j] -= mat[i][j] * temp;
                    inv[k][j] -= inv[i][j] * temp;
                }
            }
        }
    }
}

void print_matrix(float mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%0.2f\t", mat[i][j]);
        }
        printf("\n");
    }


int main() {
    float mat[N][N] = {
        {2, -1, 0},
        {-1, 2, -1},
        {0, -1, 2}
    };
    float inv[N][N];

    printf("Matrice originale:\n");
    print_matrix(mat);

    inverse_matrix(mat, inv);

    printf("\nMatrice inverse:\n");
    print_matrix(inv);

    return 0;

            
        }
        
float determinant(float **mat, int n) {
    if (n == 1) {
        return mat[0][0]; 
    }
    
    if (n == 2) {
        
        return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    }

    float det = 0;
    float **submat = (float **)malloc((n - 1) * sizeof(float *));
    for (int i = 0; i < n - 1; i++) {
        submat[i] = (float *)malloc((n - 1) * sizeof(float));
    }

    for (int k = 0; k < n; k++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == k) continue;
                submat[subi][subj] = mat[i][j];
                subj++;
            }
            subi++;
        }
        det += (k % 2 == 0 ? 1 : -1) * mat[0][k] * determinant(submat, n - 1);
    }

    for (int i = 0; i < n - 1; i++) {
        free(submat[i]);
    }
    free(submat);

    return det;
}

void print_matrix(float **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%0.2f\t", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3;
    float **mat = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        mat[i] = (float *)malloc(n * sizeof(float));
    }

    mat[0][0] = 2; mat[0][1] = -1; mat[0][2] = 0;
    mat[1][0] = -1; mat[1][1] = 2; mat[1][2] = -1;
    mat[2][0] = 0; mat[2][1] = -1; mat[2][2] = 2;

    printf("Matrice originale:\n");
    print_matrix(mat, n);

    float det = determinant(mat, n);
    printf("\nDéterminant: %0.2f\n", det);

    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}

    }

  
    
    
}
            



