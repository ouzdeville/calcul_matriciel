
#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"
#include <math.h>




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
        
    }}
    

rmat add(rmat A, rmat B){
    rmat C;
    int i,j;
    if (A.rown!=B.rown || A.coln!=B.coln)
    {
        printf("Erreur: les matrices ne sont pas de la même taille.\n");
        exit(1);
    }
    C=init(A.rown, A.coln);
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            C.coeff[i][j]=A.coeff[i][j]+B.coeff[i][j];
        }
        
    }
    
    return C;
}
rmat mult(rmat A, rmat B){
    rmat C;
    int i,j,k;
    if (A.coln!=B.rown)
    {
        printf("Erreur: les matrices ne sont pas compatibles pour la multiplication.\n");
        exit(1);
    }
    C=init(A.rown, B.coln);
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < B.coln; j++)
        {
            C.coeff[i][j]=0;
            for ( k = 0; k < A.coln; k++)
            {
                C.coeff[i][j]+=A.coeff[i][k]*B.coeff[k][j];
            }
            
        }
        
    }
    
    return C;
}
rmat transposition(rmat A){
    rmat T;
    int i,j;
    T=init(A.coln, A.rown);
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            T.coeff[j][i]=A.coeff[i][j];
        }
        
    }
    
    return T;
}


int inverse(rmat A, rmat invA) {
    if (A.rown != A.coln) {
        printf("Erreur : La matrice n'est pas carrée, donc elle n'est pas inversible.\n");
        return 0; // Retourne 0 pour indiquer une erreur
    }

    int n = A.rown;
    rmat I = init_Id(n); // Matrice identité
    rmat aug = init(n, 2 * n); // Matrice augmentée [A | I]
    int i, j, k;

    // Construire la matrice augmentée [A | I]
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            aug.coeff[i][j] = A.coeff[i][j]; // Partie A
            aug.coeff[i][j + n] = I.coeff[i][j]; // Partie I
        }
    }

    // Appliquer l'élimination de Gauss-Jordan
    for (i = 0; i < n; i++) {
        // Vérifier si le pivot est nul
        if (fabs(aug.coeff[i][i]) < 1e-6) {
            printf("Erreur : La matrice est singulière et ne peut pas être inversée.\n");
            return 0; // Retourne 0 pour indiquer une erreur
        }

        // Normaliser la ligne i
        float pivot = aug.coeff[i][i];
        for (j = 0; j < 2 * n; j++) {
            aug.coeff[i][j] /= pivot;
        }

        // Éliminer les autres lignes
        for (k = 0; k < n; k++) {
            if (k != i) {
                float factor = aug.coeff[k][i];
                for (j = 0; j < 2 * n; j++) {
                    aug.coeff[k][j] -= factor * aug.coeff[i][j];
                }
            }
        }
    }

    // Extraire la matrice inverse de la partie droite de la matrice augmentée
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            invA.coeff[i][j] = aug.coeff[i][j + n];
        }
    }

    return 1; // Retourne 1 pour indiquer le succès
}
int rang(rmat A) {
    int i, j, k;
    int rank = 0;
    rmat temp = init(A.rown, A.coln); // Copie de la matrice A

    // Copier les éléments de A dans temp
    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            temp.coeff[i][j] = A.coeff[i][j];
        }
    }

    // Appliquer l'élimination de Gauss
    for (i = 0; i < A.rown; i++) {
        if (fabs(temp.coeff[i][i]) < 1e-6) {
            continue; // Passer à la ligne suivante si le pivot est nul
        }
        rank++;
        for (j = i + 1; j < A.rown; j++) {
            float ratio = temp.coeff[j][i] / temp.coeff[i][i];
            for (k = i; k < A.coln; k++) {
                temp.coeff[j][k] -= ratio * temp.coeff[i][k];
            }
        }
    }

    return rank;
}
float det(rmat A) {
    if (A.rown != A.coln) {
        printf("Erreur : La matrice n'est pas carrée, donc le déterminant ne peut pas être calculé.\n");
        return 0.0; // Retourne 0 pour indiquer une erreur
    }

    int n = A.rown;
    rmat temp = init(n, n); // Copie de la matrice A
    int i, j, k;
    float determinant = 1.0;
    float ratio;

    // Copier les éléments de A dans temp
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            temp.coeff[i][j] = A.coeff[i][j];
        }
    }

    // Appliquer l'élimination de Gauss
    for (i = 0; i < n; i++) {
        if (fabs(temp.coeff[i][i]) < 1e-6) {
            printf("Erreur : La matrice est singulière, donc le déterminant est 0.\n");
            return 0.0; // Retourne 0 si la matrice est singulière
        }

        for (j = i + 1; j < n; j++) {
            ratio = temp.coeff[j][i] / temp.coeff[i][i];
            for (k = i; k < n; k++) {
                temp.coeff[j][k] -= ratio * temp.coeff[i][k];
            }
        }
    }

    // Calculer le déterminant comme le produit des pivots
    for (i = 0; i < n; i++) {
        determinant *= temp.coeff[i][i];
    }

    return determinant;
}
float trace(rmat A) {
    if (A.rown != A.coln) {
        printf("Erreur : La matrice n'est pas carrée, donc la trace ne peut pas être calculée.\n");
        return 0.0; // Retourne 0 pour indiquer une erreur
    }

    float sum = 0.0;
    for (int i = 0; i < A.rown; i++) {
        sum += A.coeff[i][i]; // Ajouter les éléments de la diagonale principale
    }

    return sum;
}
rmat pivot(rmat A) {
    rmat P = init(A.rown, A.coln); // Matrice pour stocker le résultat
    int i, j, k;
    float factor;

    // Copier les éléments de A dans P
    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            P.coeff[i][j] = A.coeff[i][j];
        }
    }

    // Appliquer l'élimination de Gauss
    for (i = 0; i < P.rown; i++) {
        // Vérifier si le pivot est nul
        if (P.coeff[i][i] == 0) {
            printf("Erreur : Pivot nul détecté à la ligne %d.\n", i);
            continue; // Passer à la ligne suivante
        }

        // Normaliser la ligne i
        for (j = i + 1; j < P.coln; j++) {
            P.coeff[i][j] /= P.coeff[i][i];
        }
        P.coeff[i][i] = 1;

        // Éliminer les éléments en dessous du pivot
        for (k = i + 1; k < P.rown; k++) {
            factor = P.coeff[k][i];
            for (j = i; j < P.coln; j++) {
                P.coeff[k][j] -= factor * P.coeff[i][j];
            }
        }
    }

    return P;
}