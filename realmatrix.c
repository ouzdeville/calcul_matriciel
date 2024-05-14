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
int inverse(rmat A, rmat invA){

    
}

 // Calculer l'inverse d'une matrice

//la fonction creer_sous_matrice
rmat creer_sous_matrice(rmat A, int row, int col) {
    rmat submatrix = init(A.rown - 1, A.coln - 1);

    int sub_i = 0;
    for (int i = 0; i < A.rown; i++) {
        if (i == row) continue; // Ignore la ligne spécifiée
        int sub_j = 0;
        for (int j = 0; j < A.coln; j++) {
            if (j == col) continue; // Ignore la colonne spécifiée
            submatrix.coeff[sub_i][sub_j] = A.coeff[i][j];
            sub_j++;
        }
        sub_i++;
    }

    return submatrix;
}


// la fonction calculer_determinant
float calculer_determinant(rmat A) {
    if (A.rown == 1) {
        return A.coeff[0][0]; // Cas de base : matrice 1x1
    }

    float determinant = 0;
    int sign = 1;

    for (int j = 0; j < A.coln; j++) {
        rmat submatrix = creer_sous_matrice(A, 0, j); // Créez la sous-matrice en supprimant la première ligne et la colonne j
        determinant += sign * A.coeff[0][j] * calculer_determinant(submatrix);
        sign *= -1; // Changez de signe à chaque itération
    }
 if (determinant == 0) {
        printf("Le déterminant est nul. L'inversion n'est pas possible.\n");
        return 0;
    }
    return determinant;
}
//la fonction calculer_adjoint
rmat calculer_adjoint(rmat A) {
    rmat adjoint = init(A.rown, A.coln);

    for (int i = 0; i < A.rown; i++) {
        for (int j = 0; j < A.coln; j++) {
            rmat submatrix = creer_sous_matrice(A, i, j);
            adjoint.coeff[j][i] = sign(i, j) * calculer_determinant(submatrix);
        }
    }

    return adjoint;
}

int main() {
    // Exemple d'utilisation
    int ligne = 3;
    int colonne = 3;
    rmat M = init(ligne, colonne); // Initialisez votre matrice ici

    rmat invM;
    if (inverse(M, invM)) {
        printf("Matrice inverse :\n");
        affiche(invM);
    }

  // À la fin de notre programme, après avoir utilisé M et invM :

// Libérez la mémoire allouée pour M.coeff
for (int i = 0; i < M.rown; i++) {
    free(M.coeff[i]);
}
free(M.coeff);

// Libérez la mémoire allouée pour invM.coeff
for (int i = 0; i < invM.rown; i++) {
    free(invM.coeff[i]);
}
free(invM.coeff);


    return 0;
}


// ADDITION ET MULTIPLICATION D'UNE MATRICE

rmat init_Id(int ordre) {
    rmat mat;
    int i, j;

    mat.rown = ordre;
    mat.coln = ordre;
    mat.coeff = (float **)malloc(mat.rown * sizeof(float *));

    for (i = 0; i < mat.rown; i++) {
        mat.coeff[i] = (float *)calloc(mat.coln, sizeof(float));
        for (j = 0; j < mat.coln; j++) {
            if (i == j) {
                mat.coeff[i][j] = 1.0; // Mettre 1 sur la diagonale principale
            } else {
                mat.coeff[i][j] = 0.0; // Mettre 0 partout ailleurs
            }
        }
    }

    return mat;
}

// ADDITION D'UNE MATRICE

rmat add(rmat A, rmat B) {
    rmat result;
    int i, j;

    // Vérifier si les matrices ont la même taille
    if (A.rown != B.rown || A.coln != B.coln) {
        printf("Erreur : les matrices n'ont pas la même taille.\n");
        // Renvoyer une matrice vide ou une matrice avec des valeurs par défaut
        result.rown = 0;
        result.coln = 0;
        result.coeff = NULL;
        return result;
    }

    // Initialiser la matrice résultante avec la même taille que A ou B
    result.rown = A.rown;
    result.coln = A.coln;
    result.coeff = (float **)malloc(result.rown * sizeof(float *));

    for (i = 0; i < result.rown; i++) {
        result.coeff[i] = (float *)malloc(result.coln * sizeof(float));
        for (j = 0; j < result.coln; j++) {
    // Additionner les éléments correspondants des matrices A et B
            result.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
        }
    }

    return result;
}

//MULTIPLICATION D'UNE MATRICE
rmat mult(rmat A, rmat B) {
    rmat result=init(B.rown, B.coln);
    int i, j, k;


    for (i = 0; i < result.rown; i++) {
        result.coeff[i] = (float *)malloc(result.coln * sizeof(float));
        for (j = 0; j < result.coln; j++) {
            result.coeff[i][j] = 0;
            for (k = 0; k < A.coln; k++) {
                result.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
    }

    return result;
}