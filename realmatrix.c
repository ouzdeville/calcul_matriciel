
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "realmatrix.h"

void remplirMat(rmat A)
{
    printf("Remplissage de votre matrice:\n");
        for (int i = 0; i < A.rown; i++)
        {
            for (int j = 0; j < A.coln; j++)
            {
                printf("Entrez le coefficient %d%d de votre premiere matrice:", i,j);
                scanf("%f", &A.coeff[i][j]);
            }
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

rmat init_Id(int ordre)
{
    rmat Id=init(ordre,ordre);
    for (int i = 0; i < ordre; i++)
    {
        Id.coeff[i][i]=1;
    }
    return Id;
}

rmat mult(rmat A, rmat B)
{
    
    rmat mat = init(B.rown, B.coln);
    for (int i = 0; i < A.rown; i++)
    {
        for (int j = 0; j < B.coln; j++)
        {
            float som=0;
            for (int k = 0; k < B.rown; k++)
            {
                som = som + A.coeff[i][k] * B.coeff[k][j];
            }
            mat.coeff[i][j]=som;
        }
    }
    return mat;
}

rmat add(rmat A, rmat B)
{
    rmat mat = init(B.rown, B.coln);
    for (int i = 0; i < A.rown; i++)
    {
        for (int j = 0; j < A.coln; j++)
        {
            mat.coeff[i][j]= A.coeff[i][j]  + B.coeff[i][j];
        }
    }
    return mat;
}

rmat transposition(rmat A)
{
    rmat mat = init(A.coln, A.rown);
    for (int i = 0; i < mat.rown; i++)
    {
        for (int j = 0; j < mat.coln; j++)
        {
            mat.coeff[i][j]=A.coeff[j][i];
        }
    }
    return mat;
}

rmat getMinor(rmat matrix, int row, int col)
{
    rmat minor = init(matrix.rown - 1, matrix.coln - 1);
    int minor_i = 0, minor_j = 0;

    for (int i = 0; i < matrix.rown; i++) {
        if (i == row) continue;
        minor_j = 0;
        for (int j = 0; j < matrix.coln; j++) {
            if (j == col) continue;
            minor.coeff[minor_i][minor_j] = matrix.coeff[i][j];
            minor_j++;
        }
        minor_i++;
    }

    return minor;
}

float det(rmat A) 
{
    if (A.rown != A.coln) {
        printf("Le determinant n'est defini que pour les matrices carrees.\n");
        exit(EXIT_FAILURE);
    }

    if (A.rown == 1) {
        return A.coeff[0][0];
    } else if (A.rown == 2) {
        return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
    }

    float determinant = 0.0;
    for (int j = 0; j < A.coln; j++) {
        rmat minor = getMinor(A, 0, j);
        determinant += ((j % 2 == 0) ? 1 : -1) * A.coeff[0][j] * det(minor);
        freeMatrix(minor);
    }
    return determinant;
}

voidechLigne(rmat A, int row1, int row2, int coln) {
    for (int j = 0; j < coln; j++)
    {
        float temp = A.coeff[row1][j];
        A.coeff[row1][j] = A.coeff[row2][j];
        A.coeff[row2][j] = temp;
    }
}

// Appliquer l'élimination de Gauss
rmat pivot(rmat A)
{
    rmat mat=init(A.rown, A.coln);

    for (int i = 0; i < A.rown; i++)
    {
        for (int j = 0; j < A.coln; j++)
        {
            mat.coeff[i][j] = A.coeff[i][j];
        }
    }

    for (int k = 0; k < mat.rown; k++)
    {
        // Recherche de pivot
        int maxRow = k;
        for (int i = k + 1; i < mat.rown; i++)
        {
            // Si l'element de la ligne i est plus grand en valeur absolue, mettre à jour maxRow
            if (fabs(mat.coeff[i][k]) > fabs(mat.coeff[maxRow][k]))
            {
                maxRow = i;
            }
        }

        // Echange de ligne pour mettre le pivot sur la ligne k
        if (k != maxRow)
        {
         echLigne(mat, k, maxRow, mat.coln);
        }

        // Verifier si on a une matrice singuliere.
        if (mat.coeff[k][k] == 0) 
        {
            continue;
        }

        // Elimination des elements sous le pivot
        for (int i = k + 1; i < mat.rown; i++)
        {
            float factor = mat.coeff[i][k] / mat.coeff[k][k];
            mat.coeff[i][k] = 0; // La valeur est maintenant nulle
            for (int j = k + 1; j < mat.coln; j++)
            {
                mat.coeff[i][j] -= factor * mat.coeff[k][j];
            }
        }
    }
    return mat;
}

int inverse(rmat A, rmat invA)
{
    if (A.rown != A.coln) {
        printf("L'inversion n'est possible que pour les matrices carrées.\n");
        return -1;
    }

    int n = A.rown;
    rmat aug = init(n, 2 * n); // Matrice augmentée

    // Initialiser la matrice augmentée avec A et l'identité
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug.coeff[i][j] = A.coeff[i][j];
        }
        aug.coeff[i][n + i] = 1.0;
    }

    // Élimination de Gauss-Jordan
    for (int k = 0; k < n; k++) {
        // Recherche de pivot
        int maxRow = k;
        for (int i = k + 1; i < n; i++) {
            if (fabs(aug.coeff[i][k]) > fabs(aug.coeff[maxRow][k])) {
                maxRow = i;
            }
        }

        // Échange de lignes
        if (k != maxRow) {
            echLigne(aug, k, maxRow, 2 * n);
        }

        // Vérifier si la matrice est singulière
        if (fabs(aug.coeff[k][k]) < 1e-9) {
            printf("La matrice est singulière et ne peut pas être inversée.\n");
            freeMatrix(aug);
            return -1;
        }

        // Normaliser la ligne pivot
        float pivot = aug.coeff[k][k];
        for (int j = 0; j < 2 * n; j++) {
            aug.coeff[k][j] /= pivot;
        }

        // Éliminer les autres lignes
        for (int i = 0; i < n; i++) {
            if (i != k) {
                float factor = aug.coeff[i][k];
                for (int j = 0; j < 2 * n; j++) {
                    aug.coeff[i][j] -= factor * aug.coeff[k][j];
                }
            }
        }
    }
    // Extraire la matrice inverse de la matrice augmentée
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            invA.coeff[i][j] = aug.coeff[i][n + j];
        }
    }

    affiche(invA);

    freeMatrix(aug);
    return 0;
}

int rang(rmat A)
{
    int r=0;
    for (int i = 0; i < A.rown; i++)
    {
        float som = 0;
        for (int j = 0; j < A.coln; j++)
        {
            if(A.coeff[A.rown-i-1][j]<0)
            {
                som = som - A.coeff[A.rown-i-1][j];
            }
            else
            {
                som = som + A.coeff[A.rown-i-1][j];
            }
        }

        if (som != 0)
        {
            r = r + 1;
        }
    }
    return r;
}

void freeMatrix(rmat matrix)
{
    for (int i = 0; i < matrix.rown; i++) {
        free(matrix.coeff[i]);
    }
    free(matrix.coeff);
}


