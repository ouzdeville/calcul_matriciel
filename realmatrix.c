
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
rmat add(rmat A, rmat B) {
    if (A.rown != B.rown || A.coln != B.coln) {
        printf( "impossible avec des matrice taille differente\n");
        exit(1);
    }

    rmat C = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }
    printf("l'addition des deux matrices A et B est egale à: \n");
    return C;
}
rmat mult(rmat A, rmat B) {
    if (A.coln != B.rown) {
        printf( "la multiplication est impossible car le nmbr de ligne de A est different du nmbr de colone de B \n");
        exit(EXIT_FAILURE);
    }

    rmat C = init(A.rown, B.coln);

    for ( int i = 0; i < A.rown; i++) {
        for ( int j = 0; j < B.coln; j++) {
            for ( int k = 0; k < A.coln; k++) {
                C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }
    printf("la multiplication est de A et B est egale à :\n");
    


    return C;
}

rmat transposition(rmat A) {
    rmat At = init(A.coln, A.rown); 

    for ( int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            At.coeff[j][i] = A.coeff[i][j];
        }
    }
    printf("la transposé de la matrice A est:\n");
    return At;
}



float det(rmat A) {
    if (A.rown != A.coln) {
        printf("Matrice non carrée\n");
        exit(EXIT_FAILURE);
    }

    int n = A.rown;
    if (n == 1) return A.coeff[0][0];

    float determinant = 0.0;
    int sign = 1;

    for (int f = 0; f < n; f++) {
        rmat temp = init(n - 1, n - 1); // Créer la sous-matrice en ligne dans une boucle
        for (int i = 1; i < n; i++) {
            int col_idx = 0;
            for (int j = 0; j < n; j++) {
                if (j == f) continue;
                temp.coeff[i - 1][col_idx++] = A.coeff[i][j];
            }
        }

        determinant += sign * A.coeff[0][f] * det(temp);
        sign = -sign;

        for (int i = 0; i < temp.rown; i++) free(temp.coeff[i]);
        free(temp.coeff);
    }

    return determinant;
}
 
int inverse(rmat A, rmat invA) {
    if (A.rown != A.coln) {
        printf( "La matrice n'est pas carrée, pas d'inverse possible essaie encore une fois.\n");
        return 0;
    }

    int n = A.rown;
    float determinant = det(A);
    if (determinant == 0.0f) {
        printf( "Matrice singulière, déterminant nul, pas d'inverse.\n");
        return 0;
    }

    // Calcul de l'adjointe directement
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Créer le mineur pour l'élément (i,j)
            rmat temp = init(n - 1, n - 1);
            int row = 0, col = 0;

            for (int r = 0; r < n; r++) {
                if (r == i) continue;
                col = 0;
                for (int c = 0; c < n; c++) {
                    if (c == j) continue;
                    temp.coeff[row][col] = A.coeff[r][c];
                    col++;
                }
                row++;
            }

            float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
            invA.coeff[j][i] = sign * det(temp);  // Transposée du cofacteur

            // Libérer le mineur
            for (int r = 0; r < temp.rown; r++)
                free(temp.coeff[r]);
            free(temp.coeff);
        }
    }

    // Diviser chaque élément par le déterminant
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            invA.coeff[i][j] /= determinant;

    return 1;
}



