#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct Matrix
{
	unsigned int rown;
	unsigned int coln;
	float **coeff;
} rmat;


void affiche(rmat A);
rmat init(int ligne, int colonne);
rmat init_Id(int ordre);
rmat add(rmat A, rmat B);
rmat mult(rmat A, rmat B);
rmat transposition(rmat A);
int inverse(rmat A, rmat invA);
float det(rmat A);
rmat pivot(rmat A);
int rang(rmat A);
void free_matrix(rmat A);

int main()
{
    int rowMat1, colMat1, rowMat2, colMat2;
    printf("Entrez le nombre de lignes de la premiere matrice : ");
    do{
        scanf("%d", &rowMat1);
    } while (rowMat1<=0);

    printf("Entrez le nombre de colonnes premiere matrice : ");
    do{
        scanf("%d", &colMat1);
    } while (colMat1<=0);

    printf("\nEntrez le nombre de lignes seconde matrice : ");
    do{
        scanf("%d", &rowMat2);
    } while (rowMat2<=0);

    printf("Entrez le nombre de colonnes seconde matrice : ");
    do{
        scanf("%d", &colMat2);
    } while (colMat2<=0);
