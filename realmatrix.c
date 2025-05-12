
#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"



rmat init(int ligne, int colonne){

    rmat mat;
    int i=0;
    mat.rown=ligne;
    mat.coln=colonne;
    // je déclare un tableau contenant des tableaux (float *)
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
        rmat C;
        int i, j;

        if (A.rown != B.rown || A.coln != B.coln) {
            printf("Erreur : dimensions incompatibles pour l'addition\n");
            exit(1);
        }
        C = init(A.rown, A.coln);
        for (i = 0; i < A.rown; i++) {
            for(j = 0; j < A.coln; j++) {
                C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
            }
        }
        return C;
    }

    // multiplication
   rmat mult(rmat A, rmat B) {
        if (A.coln != B.rown)
        {
            printf("\n Mutltiplication impossible\n");
            exit(-1);
        }
        rmat C = init(A.rown,B.coln);
        for (int i = 0; i < A.rown; i++)
        {
            for (int j = 0; j < B.coln;j++){
                int tmp = 0;
                for (int k = 0;k < A.coln; k++){
                    tmp += A.coeff[i][k]*B.coeff[k][j];
                }
                C.coeff[i][j] = tmp;
            }
        }
        return C;
    }

    // transposition
   rmat transposition(rmat A) {
        rmat C = init(A.coln,A.rown);
        for(int i = 0; i < A.rown;i++){
            for (int j = 0; j < A.coln; j++){
                C.coeff[j][i] = A.coeff[i][j];
            }
        }
        return C;
    }

    //inverse
    int inverse(rmat A, rmat invA) {
        if (A.rown != A.coln) {
            printf("Erreur : la matrice n'est pas carree\n");
            return 0;
        }

        int n = A.rown;
        int i,j,k;
        float pivot, ratio;

        rmat temp = init(n, n);
        for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
    temp.coeff[i][j] = A.coeff[i][j];

    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
         invA.coeff[i][j] = (i == j) ? 1.0 : 0.0;

    for (i = 0; i < n; i++) {
        float pivot = temp.coeff[i][i];
        if (pivot == 0.0) {
            printf("pivot nul : matrice non inversible\n");
            return 0;
        }

        for (j = 0; j < n; j++) {
            temp.coeff[i][j] /= pivot;
            invA.coeff[i][j] /= pivot;
        }

        for (k = 0; k < n; k++) {
            if (k != i) {
                ratio = temp.coeff[k][i];
                for (j = 0; j < n; j++) {
                temp.coeff[k][j] -= ratio * temp.coeff[i][j];
            invA.coeff[k][j] -= ratio * invA.coeff[i][j];
         }
        }
    }
}
return 1;
}

//determinant
float det(rmat A) {
    if (A.rown != A.coln) {
        printf("Erreur : matrice non caree\n");
        return 0.0;
    }
    int n = A.rown;

    if (n == 1) {
        return A.coeff[0][0];
    }
    if ( n == 2) {
        return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];

    }
    float determinant = 0.0;
    for (int k = 0; k < n; k++) {
        rmat sub = init(n - 1, n - 1);
        for (int i = 1; i < n; i++) {
            int col = 0;
            for (int j = 0; j < n; j++) {
            if ( j == k) continue;
            sub.coeff[i - 1][col] = A.coeff[i][j];
            col++;
        }
    }
    float sign = (k % 2 == 0) ? 1.0 : -1.0;
    determinant += sign * A.coeff[0][k] * det(sub);

    for (int i = 0; i < sub.rown; i++)
    free(sub.coeff[i]);
free(sub.coeff);
}
return determinant;
}

 
