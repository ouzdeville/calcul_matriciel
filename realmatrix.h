#ifndef _RMATRIX_H
#define _RMATRIX_H

typedef struct Matrix {
	unsigned int rown;
	unsigned int coln;
	float **coeff;
} rmat;

void affiche(rmat A);
rmat init(int ligne, int colonne);
rmat init_Id(int ordre);
void fill_matrix(rmat *mat);
rmat add(rmat A, rmat B);
rmat mult(rmat A, rmat B);
rmat transposition(rmat A);
int inverse(rmat A, rmat *invA);
void free_matrix(rmat mat);
rmat get_cofactor(rmat mat, int p, int q, int n);
float determinant(rmat A);
float trace(rmat A);
rmat pivot(rmat *mat);
int rang(rmat A);
float* valeurPropre(rmat A);
int dimEspacePropre(rmat A, float lamda);
#endif
