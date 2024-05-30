
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

rmat transposition(rmat A){
     rmat T = init(A.coln, A.rown);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            T.coeff[j][i] = A.coeff[i][j];
        }
    }
    return T;
}

float det(rmat A);
 rmat submatrix(rmat A, int row, int col);

float det(rmat A) {
    if (A.rown != A.coln) {
        printf("La matrice doit être carrée pour calculer le déterminant.\n");
        return 0;
    }

    int n = A.rown;

    if (n == 1) {
        return A.coeff[0][0];
    }

    if (n == 2) {
        return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
    }

    float determinant = 0;
    for (int j = 0; j < n; j++) {
        rmat sub = submatrix(A, 0, j);
        determinant += (j % 2 == 0 ? 1 : -1) * A.coeff[0][j] * det(sub);
       for (int i = 0; i < sub.rown; i++) {
            free(sub.coeff[i]);
        }
       free(sub.coeff);
   }

    return determinant;
}

 rmat submatrix(rmat A, int row, int col) {
     rmat sub = init(A.rown - 1, A.coln - 1);
     int subi = 0;
     for (int i = 0; i < A.rown; i++) {
       if (i == row) continue;
        int subj = 0;
       for (int j = 0; j < A.coln; j++) {
            if (j == col) continue;
           sub.coeff[subi][subj] = A.coeff[i][j];
           subj++;
        }
         subi++;
     }
     return sub;
}


rmat pivot(rmat A) {
    int n = A.rown;
    int m = A.coln;
    rmat P = init(n, m);

    // Copie la matrice A dans P
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            P.coeff[i][j] = A.coeff[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        // Trouver le pivot dans la colonne i 
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(P.coeff[k][i]) > abs(P.coeff[maxRow][i])) {
                maxRow = k;
            }
        }

        // Échange les lignes 
        if (i != maxRow) {
            float *temp = P.coeff[i];
            P.coeff[i] = P.coeff[maxRow];
            P.coeff[maxRow] = temp;
        }

        // Élimination de Gauss
        for (int k = i + 1; k < n; k++) {
            float c = P.coeff[k][i] / P.coeff[i][i];
            for (int j = i; j < m; j++) {
                if (i == j) {
                    P.coeff[k][j] = 0;
                } else {
                    P.coeff[k][j] -= c * P.coeff[i][j];
                }
            }
        }
    }

    return P;
}

int rang(rmat A) {
    rmat P = pivot(A);
    int M = 0;
    for (int i = 0; i < P.rown; i++) {
        int row_zero = 1;
        for (int j = 0; j < P.coln; j++) {
            if (P.coeff[i][j] != 0) {
                row_zero = 0;
                break;
            }
        }
        if (!row_zero) {
            M++;
        }
    }
}

