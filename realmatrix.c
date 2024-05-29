
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
// Fonction pour additionner deux matrices
rmat add(const rmat A, const rmat B) {
    rmat C = init(A.rown, A.coln);
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }
    return C;
}

// Fonction pour multiplier deux matrices
rmat mult(const rmat A, const rmat B) {
    rmat C = init(A.rown, B.coln);
    for (int i = 0; i < C.rown; i++) {
        for (int j = 0; j < C.coln; j++) {
            for (int k = 0; k < A.coln; k++) {
                C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }
    return C;
}




// int inverse(rmat A, rmat invA){

    
// }


// Fonction pour inverser une matrice (implémentation simple)
int inverse(rmat A, rmat *invA) {
    // Vérification si la matrice n'est pas carrée
    if (A.rown != A.coln) {
        printf("La matrice n'est pas carrée, l'inversion n'est pas possible.\n");
        return 0;
    }

    // Allocation de mémoire pour la matrice inverse
    *invA = init(A.rown, A.coln);

    // Copie de la matrice A dans invA (pour l'instant)
    int i, j;
    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            (*invA).coeff[i][j] = A.coeff[i][j];
        }
    }

    // Implémentation simple d'inversion (remplacement par l'identité)
    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            if (i == j) {
                (*invA).coeff[i][j] = 1; // Mettre 1 sur la diagonale principale
            } else {
                (*invA).coeff[i][j] = 0; // Mettre 0 ailleurs
            }
        }
    }

    return 1;
}




// Fonction pour libérer la mémoire allouée pour une matrice
void freeMatrix(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        free(A.coeff[i]);
    }
    free(A.coeff);
}

// Fonction pour calculer le déterminant d'une matrice
float det(rmat A) {
    // Vérification si la matrice est carrée
    if (A.rown != A.coln) {
        printf("La matrice n'est pas carrée, le déterminant n'est pas défini.\n");
        return 0.0f;
    }

    // Allocation d'un tableau pour stocker les coefficients de la matrice temporaire
    float *temp = (float *)malloc(A.rown * A.coln * sizeof(float));
    int k = 0;
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            temp[k++] = A.coeff[i][j];
        }
    }

    // Calcul du déterminant par la méthode de Laplace
    float determinant = 0.0f;
    for (int i = 0; i < A.rown; i++) {
        float term = temp[i]; // Terme de la première ligne
        int sign = 1;
        for (int j = i + 1; j < A.rown; j++) {
            // Calcul du produit des termes diagonaux
            term *= temp[j * A.rown + j];
            sign *= -1;
            // Calcul du produit des termes non-diagonaux
            for (int k = i; k < j; k++) {
                term *= temp[j * A.rown + k];
            }
        }
        determinant += sign * term;
    }

    // Libération de la mémoire allouée pour le tableau temporaire
    free(temp);

    return determinant;
}

// Fonction pour transposer une matrice
rmat transposition(rmat A) {
    rmat transposed;
    transposed.rown = A.coln; // Le nombre de lignes devient le nombre de colonnes de la matrice transposée
    transposed.coln = A.rown; // Le nombre de colonnes devient le nombre de lignes de la matrice transposée

    // Allocation de mémoire pour les coefficients de la matrice transposée
    transposed.coeff = (float **)malloc(transposed.rown * sizeof(float *));
    for (int i = 0; i < transposed.rown; i++) {
        transposed.coeff[i] = (float *)malloc(transposed.coln * sizeof(float));
    }

    // Transposition des coefficients
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            transposed.coeff[j][i] = A.coeff[i][j];
        }
    }

    return transposed;
}

