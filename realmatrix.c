#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "realmatrix.h"


void affiche(rmat A)
{
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

rmat init(int ligne, int colonne)
{
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


// Fonction d'initialisation d'une identité de matrices.
rmat init_Id(int ordre)
{
    rmat mat = init(ordre, ordre); // Initialize a square matrix of size n x n

    // Set diagonal elements to 1
    for (int i = 0; i < ordre; i++) {
        mat.coeff[i][i] = 1.0;
    }

    // Set other elements to 0
    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            if (i != j) {
                mat.coeff[i][j] = 0.0;
            }
        }
    }

    return mat;
}


// Fonction d'addition de deux matrices
rmat add(rmat A, rmat B)
{
    // Vérification de la compatibilité des dimensions
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Les matrices doivent avoir les mêmes dimensions (meme nombre de lignes et de colonnes) pour l'addition.\n");
        exit(1);
    }

    rmat C = init(A.rown, A.coln);

    // Addition des éléments correspondants des matrices
    for (int i=0; i<A.rown ; i++) {
        for (int j = 0; j < A.coln; j++) {
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }

    return C;
}


// Fonction de multiplication de deux matrices
rmat mult(rmat A, rmat B) {
    // Vérification de la compatibilité des dimensions
    if (A.coln != B.rown) {
        printf("Le nombre de colonnes de la premiere matrice doit être égal au nombre de lignes de la seconde matrice pour la multiplication.\n");
        exit(1);
    }

    rmat C = init(A.rown, B.coln);

    // Multiplication des éléments des matrices
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < B.coln; j++) {
            for (int k = 0; k < A.coln; k++) {
                C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }

    return C;
}


// Fonction de transposition d'une matrice
rmat transposition(rmat A) {
    rmat B = init(A.coln, A.rown);

    // Transposition des éléments de la matrice
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            B.coeff[j][i] = A.coeff[i][j];
        }
    }

    return B;
}


// Fonction de calcul de l'inverse d'une matrice (élimination gaussienne avec pivoting partiel)
int inverse(rmat A, rmat invA) {
    int n = A.rown;

    // Vérifier si la matrice est carrée
    if (A.rown != A.coln) {
        printf("La matrice doit être carree pour calculer l'inverse.\n");
        return 0;
    }

    // Initialiser la matrice identité et la matrice augmentée
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

    // Élimination gaussienne avec pivoting partiel
    for (int i = 0; i < n; i++) {
        // Pivoting partiel
        int max_row = i;
        float max_value = fabs(aug.coeff[i][i]);
        for (int k = i + 1; k < n; k++) {
            if (fabs(aug.coeff[k][i]) > max_value) {
                max_row = k;
                max_value = fabs(aug.coeff[k][i]);
            }
        }

        // Échanger les lignes si nécessaire
        if (max_row != i) {
            for (int j = 0; j < 2 * n; j++) {
                float temp = aug.coeff[i][j];
                aug.coeff[i][j] = aug.coeff[max_row][j];
                aug.coeff[max_row][j] = temp;
            }
        }

        // Éliminer les éléments non nuls sous la diagonale de la ligne i
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

    // Retour en arrière pour obtenir l'inverse
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            float factor = aug.coeff[i][j] / aug.coeff[i][i];
            for (int k = 0; k < n; k++) {
                aug.coeff[i][k] -= factor * aug.coeff[j][k];
            }
        }

        // Normaliser la ligne i
        if (aug.coeff[i][i] != 1.0) {
            for (int k = 0; k < n; k++) {
                aug.coeff[i][k] /= aug.coeff[i][i];
            }
        }
    }

    // Copier l'inverse dans la matrice invA
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            invA.coeff[i][j] = aug.coeff[i][j + n];
        }
    }

    // Libérer la mémoire des matrices temporaire.
}


// Fonction de calcul du déterminant d'une matrice carrée
float det(rmat A) {
    if (A.rown != A.coln) {
        printf("Erreur : la matrice doit être carree pour calculer le déterminant.\n");
        exit(EXIT_FAILURE);
    }

    int n = A.rown;

    // Si la matrice est de taille 1x1, le déterminant est simplement le seul élément de la matrice
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


// Fonction de calcul du pivot d'une matrice
rmat pivot(rmat A) {
    int i, j, max_row;
    float max_value;

    // Parcourir chaque colonne
    for (j = 0; j < A.coln; j++) {
        max_row = 0;
        max_value = A.coeff[0][j];

        // Trouver l'élément pivot dans la colonne
        for (i = 1; i < A.rown; i++) {
            if (fabs(A.coeff[i][j]) > max_value) {
                max_row = i;
                max_value = A.coeff[i][j];
            }
        }

        // Échanger les lignes contenant l'élément pivot et la ligne actuelle
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


// Fonction de calcul du rang d'une matrice
int rang(rmat A) {
    // Réduire la matrice à sa forme échelonnée par élimination gaussienne
    A = pivot(A);
    rmat B = init(A.rown, A.coln);

    // Copier la matrice pivotée dans une nouvelle matrice
    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            B.coeff[i][j] = A.coeff[i][j];
        }
    }

    int rank = 0;
    for (int i = 0; i < A.rown; i++) {
        // Vérifier si la ligne i est non nulle
        int nonZero = 0;
        for (int j = 0; j < A.coln; j++) {
            if (B.coeff[i][j] != 0) {
                nonZero = 1;
                break;
            }
        }

        if (nonZero) {
            rank++;

            // Éliminer les éléments non nuls sous la diagonale de la ligne i
            for (int k = i + 1; k < A.rown; k++) {
                float factor = B.coeff[k][i] / B.coeff[i][i];
                for (int j = 0; j < A.coln; j++) {
                    B.coeff[k][j] -= factor * B.coeff[i][j];
                }
            }
        }
    }

    return rank;
}

// Fonction pour libérer la mémoire allouée pour une matrice
void free_matrix(rmat A) {
    for (int i = 0; i < A.rown; i++) {
        free(A.coeff[i]); // Libère chaque ligne
    }
    free(A.coeff); // Libère le tableau de pointeurs de lignes
}