
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

rmat add(rmat A, rmat B);{
    // Vérification que les matrices ont les mêmes dimensions
    if (A.rown != B.rown || A.coln != B.coln) {
        fprintf(stderr, "Erreur [add()]: Dimensions incompatibles (%ux%u) + (%ux%u)\n", 
                A.rown, A.coln, B.rown, B.coln);
        exit(EXIT_FAILURE);  // On quitte le programme en cas d'erreur grave
    }

    // Initialisation de la matrice résultat
    rmat result = init(A.rown, A.coln);

    // Parcours et addition élément par élément
    for (unsigned int i = 0; i < A.rown; i++) {
        for (unsigned int j = 0; j < A.coln; j++) {
            result.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }

    return result;
}
rmat mult(rmat A, rmat B) {
    if (A.coln != B.rown) {
        fprintf(stderr, "Erreur [mult()]: Dimensions incompatibles (%ux%u) × (%ux%u)\n",
                A.rown, A.coln, B.rown, B.coln);
        exit(EXIT_FAILURE);
    }

    rmat C = init(A.rown, B.coln);
    
    for (unsigned int i = 0; i < A.rown; i++) {
        for (unsigned int j = 0; j < B.coln; j++) {
            float sum = 0;
            for (unsigned int k = 0; k < A.coln; k++) {
                sum += A.coeff[i][k] * B.coeff[k][j];
            }
            C.coeff[i][j] = sum;
        }
    }
    return C;
}
rmat transposition(rmat A) {
    rmat T = init(A.coln, A.rown);
    
    for (unsigned int i = 0; i < A.rown; i++) {
        for (unsigned int j = 0; j < A.coln; j++) {
            T.coeff[j][i] = A.coeff[i][j];
        }
    }
    return T;
}
float trace(rmat A) {
    if (A.rown != A.coln) {
        fprintf(stderr, "Erreur [trace()]: La matrice n'est pas carrée (%ux%u)\n",
                A.rown, A.coln);
        exit(EXIT_FAILURE);
    }

    float tr = 0;
    for (unsigned int i = 0; i < A.rown; i++) {
        tr += A.coeff[i][i];
    }
    return tr;
}
float det(rmat A) {
    if (A.rown != A.coln) {
        fprintf(stderr, "Erreur [det()]: La matrice n'est pas carrée (%ux%u)\n",
                A.rown, A.coln);
        exit(EXIT_FAILURE);
    }

    // Cas de base
    if (A.rown == 1) return A.coeff[0][0];
    if (A.rown == 2) {
        return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
    }

    float determinant = 0;
    for (unsigned int k = 0; k < A.coln; k++) {
        // Création de la sous-matrice
        rmat sub = init(A.rown-1, A.coln-1);
        for (unsigned int i = 1; i < A.rown; i++) {
            unsigned int sub_j = 0;
            for (unsigned int j = 0; j < A.coln; j++) {
                if (j == k) continue;
                sub.coeff[i-1][sub_j++] = A.coeff[i][j];
            }
        }
        
        // Calcul récursif
        float sign = (k % 2 == 0) ? 1 : -1;
        determinant += sign * A.coeff[0][k] * det(sub);
        free_matrix(sub);
    }
    return determinant;
}
int inverse(rmat A, rmat *invA) {
    if (A.rown != A.coln) {
        printf("Erreur : matrice non carrée\n");
        return 0;
    }

    int n = A.rown;
    *invA = init_Id(n);

    rmat temp = init(n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp.coeff[i][j] = A.coeff[i][j];

    for (int i = 0; i < n; i++) {
        if (temp.coeff[i][i] == 0) {
            int j = i + 1;
            while (j < n && temp.coeff[j][i] == 0) j++;
            if (j == n) {
                printf("Erreur : matrice singulière\n");
                return 0;
            }
            float* tmp = temp.coeff[i];
            temp.coeff[i] = temp.coeff[j];
            temp.coeff[j] = tmp;

            tmp = invA->coeff[i];
            invA->coeff[i] = invA->coeff[j];
            invA->coeff[j] = tmp;

        }

        float pivot = temp.coeff[i][i];
        for (int j = 0; j < n; j++) {
            temp.coeff[i][j] /= pivot;
            invA->coeff[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                float factor = temp.coeff[k][i];
                for (int j = 0; j < n; j++) {
                    temp.coeff[k][j] -= factor * temp.coeff[i][j];
                    invA->coeff[k][j] -= factor * invA->coeff[i][j];
                }
            }
        }
    }

    return 1;
}