
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
/*-------------------------------Fonction pour afficher la  matrice---------------------------------*/
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

/*-------------------------------Fonction pour liberer la memoire Allouer pour une matrice---------------------------------*/
void free_matrix(rmat mat) {
    for (int i = 0; i < mat.rown; i++) {
        free(mat.coeff[i]);
    }
    free(mat.coeff);
}

/*-------------------------------Fonction pour remplir une matrice---------------------------------*/
void fill_matrix(rmat *mat) {
    for (int i = 0; i < mat->rown; i++) {
        for (int j = 0; j < mat->coln; j++) {
            printf("Entrez la valeur pour l'élément [%d][%d]: ", i, j);
            scanf("%lf", &(mat->coeff[i][j]));
        }
    }
}


/*-------------------------------------Addition d'une matrice-----------------------------------------*/
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

/*-------------------------------------Multiplication d'une matrice-----------------------------------------*/
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

/*-------------------------------------Transposition d'une matrice-----------------------------------------*/

rmat transposition(rmat A) {
    rmat T = init(A.coln, A.rown);  // Dimensions inversées pour la transpose
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            T.coeff[j][i] = A.coeff[i][j];
        }
    }
    return T;
}

/*-------------------------------------pivot d'une matrice-----------------------------------------------*/

rmat pivot(rmat *A) {
    int i, j, k;
    int n = A->rown;
    int m = A->coln;

    for (i = 0; i < n; i++) {
        // Trouver le pivot
        double maxEl = fabs(A->coeff[i][i]);
        int maxRow = i;
        for (k = i + 1; k < n; k++) {
            if (fabs(A->coeff[k][i]) > maxEl) {
                maxEl = fabs(A->coeff[k][i]);
                maxRow = k;
            }
        }

        // Échanger les lignes
        for (k = i; k < m; k++) {
            double tmp = A->coeff[maxRow][k];
            A->coeff[maxRow][k] = A->coeff[i][k];
            A->coeff[i][k] = tmp;
        }

        // Mettre à 1 le pivot
        for (k = i + 1; k < m; k++) {
            A->coeff[i][k] /= A->coeff[i][i];
        }
        A->coeff[i][i] = 1.0;

        // Rendre les autres éléments de la colonne égaux à 0
        for (j = 0; j < n; j++) {
            if (j != i) {
                double c = A->coeff[j][i];
                for (k = i; k < m; k++) {
                    if (i == k) {
                        A->coeff[j][k] = 0;
                    } else {
                        A->coeff[j][k] -= c * A->coeff[i][k];
                    }
                }
            }
        }
    }
}

/*-------------------------------------determinant d'une matrice-----------------------------------------------*/

//Fonction pour oobtenir la matrice des cofacteurs
rmat get_cofactor(rmat A, int p, int q, int n) {
    int i = 0, j = 0;
    rmat temp = init(n - 1, n - 1);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp.coeff[i][j++] = A.coeff[row][col];

                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
    return temp;
}

// Fonction pour calculer le determinant d'une matrice
float determinant(rmat A) {
    if (A.rown != A.coln) {
        fprintf(stderr, "Erreur : Le déterminant ne peut être calculé que pour les matrices carrées.\n");
        exit(EXIT_FAILURE);
    }

    int n = A.rown;

    if (n == 1) {
        return A.coeff[0][0];
    }

    if (n == 2) {
        return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
    }

    double det = 0;
    int sign = 1;

    for (int f = 0; f < n; f++) {
        rmat temp = get_cofactor(A, 0, f, n);
        det += sign * A.coeff[0][f] * determinant(temp);
        sign = -sign;
        free_matrix(temp);
    }

    return det;
}

/*---------------------------------------Inverse d'une matrice------------------------------------------------*/

int inverse(rmat A, rmat *invA) {
    if (A.rown != A.coln) {
        fprintf(stderr, "Erreur : Seules les matrices carrées peuvent être inversées.\n");
        return 0;  // Erreur
    }

    int n = A.rown;
    rmat aug = init(n, 2 * n);

    // Construire la matrice augmentée [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug.coeff[i][j] = A.coeff[i][j];
            aug.coeff[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Appliquer l'algorithme de Gauss-Jordan
    for (int i = 0; i < n; i++) {
        // Trouver le pivot
        double maxEl = fabs(aug.coeff[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(aug.coeff[k][i]) > maxEl) {
                maxEl = fabs(aug.coeff[k][i]);
                maxRow = k;
            }
        }

        // Échanger les lignes
        for (int k = 0; k < 2 * n; k++) {
            double tmp = aug.coeff[maxRow][k];
            aug.coeff[maxRow][k] = aug.coeff[i][k];
            aug.coeff[i][k] = tmp;
        }

        // Mettre à 1 le pivot
        double pivot = aug.coeff[i][i];
        if (pivot == 0) {
            fprintf(stderr, "Erreur : Matrice non inversible.\n");
            free_matrix(aug);
            return 0;  // Erreur
        }
        for (int k = 0; k < 2 * n; k++) {
            aug.coeff[i][k] /= pivot;
        }

        // Rendre les autres éléments de la colonne égaux à 0
        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = aug.coeff[j][i];
                for (int k = 0; k < 2 * n; k++) {
                    aug.coeff[j][k] -= factor * aug.coeff[i][k];
                }
            }
        }
    }

    // Extraire la matrice inverse
    *invA = init(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            invA->coeff[i][j] = aug.coeff[i][j + n];
        }
    }

    free_matrix(aug);
    return 1;  // Succès
}

/*---------------------------------------Rang d'une matrice------------------------------------------------*/

int rang(rmat A) {
    int rank = 0;
    int n = A.rown;
    int m = A.coln;
    
    // Appliquer l'algorithme de Gauss-Jordan
    for (int row = 0; row < n; row++) {
        if (fabs(A.coeff[row][row]) > 1e-6) {
            for (int col = 0; col < m; col++) {
                if (col != row) {
                    double factor = A.coeff[col][row] / A.coeff[row][row];
                    for (int k = 0; k < m; k++) {
                        A.coeff[col][k] -= factor * A.coeff[row][k];
                    }
                }
            }
        }
    }

    // Compter le nombre de lignes non nulles
    for (int row = 0; row < n; row++) {
        int nonZero = 0;
        for (int col = 0; col < m; col++) {
            if (fabs(A.coeff[row][col]) > 1e-6) {
                nonZero = 1;
                break;
            }
        }
        rank += nonZero;
    }

    return rank;
}
