
#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"



rmat init(int ligne, int colonne){

    rmat mat;
    int i=0;
    mat.rown=ligne;
    mat.coln=colonne;

    mat.coeff=(float **) malloc(mat.rown *sizeof(float *));
    for ( i = 0; i < mat.rown; i++)
    {

        mat.coeff[i]= calloc(mat.coln, sizeof(float));
    }

    return mat;
}
    rmat A = init(rowMat1, colMat1);
    rmat B = init(rowMat2, colMat2);

    for(int i=0 ; i<rowMat1 ; i++){
        for(int j=0 ; j<colMat1 ; j++){
            A.coeff[i][j] = rand()%10;
        }
    }

    for(int i=0 ; i<rowMat2 ; i++){
        for(int j=0 ; j<colMat2 ; j++){
            B.coeff[i][j] = rand()%10;
        }
    }


    printf("\nMatrice A :\n");
    affiche(A);

    printf("\nMatrice B :\n");
    affiche(B);
    printf("\n");









rmat add(rmat A, rmat B){
    rmat C=init(A.rown,A.coln);
    int i=0, j=0;
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            C.coeff[i][j]= A.coeff[i][j]+ B.coeff[i][j];
        }

    }

    return C;
}
rmat mult(rmat A, rmat B){
    rmat C=init(A.rown,B.coln);
    int i=0, j=0,k;
    for ( i = 0; i < C.rown; i++)
    {
        for ( j = 0; j < C.coln; j++)
        {
            for ( k = 0; k < A.coln; k++)
            {
                C.coeff[i][j]+= A.coeff[i][k]* B.coeff[k][j];
            }


        }

    }

    return C;

}


rmat transposition(rmat A) {
    rmat B = init(A.coln, A.rown);


    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            B.coeff[j][i] = A.coeff[i][j];
        }
    }

    return B;
}

int inverse(rmat A, rmat invA) {
    int n = A.rown;


    if (A.rown != A.coln) {
        printf("La matrice doit être carree pour calculer l'inverse.\n");
        return 0;
    }


    rmat I = init_Id(n);
    rmat aug = init(n, 2 * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug.coeff[i][j] = A.coeff[i][j];
        }
        for (int j = n; j < 2 * n; j++) {
            if (i == j) {
                aug.coeff[i][j] = 1.0;
            } else {
                aug.coeff[i][j] = 0.0;
            }
        }
    }

    for (int i = 0; i < n; i++) {



        int max_row = i;
        float max_value = fabs(aug.coeff[i][i]);
        for (int k = i + 1; k < n; k++) {
            if (fabs(aug.coeff[k][i]) > max_value) {
                max_row = k;
                max_value = fabs(aug.coeff[k][i]);
            }
        }


        if (max_row != i) {
            for (int j = 0; j < 2 * n; j++) {
                float temp = aug.coeff[i][j];
                aug.coeff[i][j] = aug.coeff[max_row][j];
                aug.coeff[max_row][j] = temp;
            }
        }


        if (aug.coeff[i][i] == 0.0) {
            printf("La matrice est singuliere.\n");
            return 0;
        }

        for (int k = i + 1; k < n; k++) {
            float factor = aug.coeff[k][i] / aug.coeff[i][i];
            for (int j = 0; j < 2 * n; j++) {
                aug.coeff[k][j] -= factor * aug.coeff[i][j];
            }
        }
    }


    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            float factor = aug.coeff[i][j] / aug.coeff[i][i];
            for (int k = 0; k < n; k++) {
                aug.coeff[i][k] -= factor * aug.coeff[j][k];
            }
        }


        if (aug.coeff[i][i] != 1.0) {
            for (int k = 0; k < n; k++) {
                aug.coeff[i][k] /= aug.coeff[i][i];
            }
        }
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            invA.coeff[i][j] = aug.coeff[i][j + n];
        }
    }


}



float det(rmat A) {
    if (A.rown != A.coln) {
        printf("Erreur : la matrice doit être carree pour calculer le déterminant.\n");
        exit(EXIT_FAILURE);
    }

    int n = A.rown;


    if (n == 1) {
        return A.coeff[0][0];
    }

 float determinant = 0;
    rmat temp = init(n - 1, n - 1);

    for (int i = 0; i < n; i++) {
        int temp_i = 0;
        for (int j = 1; j < n; j++) {
            int temp_j = 0;
            for (int k = 0; k < n; k++) {
                if (k != i) {
                    temp.coeff[temp_i][temp_j++] = A.coeff[j][k];
                }
            }
            temp_i++;
        }
        determinant += A.coeff[0][i] * pow(-1, i) * det(temp);
    }

    free_matrix(temp);
    return determinant;
}

rmat pivot(rmat A) {
    int i, j, max_row;
    float max_value;


    for (j = 0; j < A.coln; j++) {
        max_row = 0;
        max_value = A.coeff[0][j];


        for (i = 1; i < A.rown; i++) {
            if (fabs(A.coeff[i][j]) > max_value) {
                max_row = i;
                max_value = A.coeff[i][j];
            }
        }


        if (max_row != 0) {
            for (int k = 0; k < A.coln; k++) {
                float temp = A.coeff[max_row][k];
                A.coeff[max_row][k] = A.coeff[0][k];
                A.coeff[0][k] = temp;
            }
        }
    }

    return A;
}



int rang(rmat A) {

    A = pivot(A);
    rmat B = init(A.rown, A.coln);


    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            B.coeff[i][j] = A.coeff[i][j];
        }
    }

    int bang = 0;
    for (int i = 0; i < A.rown; i++) {

        int nonZero = 0;
        for (int j = 0; j < A.coln; j++) {
            if (B.coeff[i][j] != 0) {
                nonZero = 1;
                break;
            }
        }

        if (nonZero) {
            bang++;


            for (int k = i + 1; k < A.rown; k++) {
                float factor = B.coeff[k][i] / B.coeff[i][i];
                for (int j = 0; j < A.coln; j++) {
                    B.coeff[k][j] -= factor * B.coeff[i][j];
                }
            }
        }
    }

    return bang;
}


    for (int i = 0; i < A.rown; i++) {
        free(A.coeff[i]);
    }
    free(A.coeff);
}




