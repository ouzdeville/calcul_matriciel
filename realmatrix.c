
#include <stdlib.h>
#include <stdio.h>
#include <realmatrix.h>



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

rmat init_Id(int ordre){
    rmat mat;
    int i=0;
    mat=init(ordre, ordre);
     for ( i = 0; i < mat.rown; i++)
    {
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



rmat transposition(rmat A) {
    rmat T = init(A.coln, A.rown);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            T.coeff[j][i] = A.coeff[i][j];
        }
    }
    return T;
}



int inverse(rmat A, rmat invA) {
    if (A.rown != 3 || A.coln != 3) {
        printf("La fonction inverse est uniquement pour les matrices 3x3.\n");
        return -1;
    }

    float det = determinant3x3(A);
    if (det == 0) {
        printf("La matrice n'est pas inversible.\n");
        return -1;
    }

    invA = inverse3x3(A);
    return 0;
}


float det(rmat A) {
    if (A.rown != 3 || A.coln != 3) {
        printf("Le déterminant peut être calculé seulement pour une matrice 3x3.\n");
        return 0;
    }
    float det = 0;
    det += A.coeff[0][0] * (A.coeff[1][1] * A.coeff[2][2] - A.coeff[1][2] * A.coeff[2][1]);
    det -= A.coeff[0][1] * (A.coeff[1][0] * A.coeff[2][2] - A.coeff[1][2] * A.coeff[2][0]);
    det += A.coeff[0][2] * (A.coeff[1][0] * A.coeff[2][1] - A.coeff[1][1] * A.coeff[2][0]);
    return det;
}

float det(rmat A) {
    return determinant3x3(A);
}




rmat pivot(rmat A) {
    rmat P = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            P.coeff[i][j] = A.coeff[i][j];
        }
    }

    for (int i = 0; i < P.rown; i++) {
        float pivot = P.coeff[i][i];
        if (pivot != 0) {
            for (int j = 0; j < P.coln; j++) {
                P.coeff[i][j] /= pivot;
            }
        }

        for (int k = 0; k < P.rown; k++) {
            if (k != i) {
                float factor = P.coeff[k][i];
                for (int j = 0; j < P.coln; j++) {
                    P.coeff[k][j] -= factor * P.coeff[i][j];
                }
            }
        }
    }
    return P;
}


int rang(rmat A) {
    rmat P = pivot(A);
    int rank = 0;
    for (int i = 0; i < P.rown; i++) {
        for (int j = 0; j < P.coln; j++) {
            if (P.coeff[i][j] != 0) {
                rank++;
                break;
            }
        }
    }
    return rank;
}



