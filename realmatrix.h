#ifndef _RMATRIX_H
#define _RMATRIX_H

typedef struct Matrix {
	unsigned int rown;
	unsigned int coln;
	float **coeff;
} rmat;

void remplirMat(rmat A);
void affiche(rmat A);
rmat init(int ligne, int colonne);
rmat init_Id(int ordre);
rmat add(rmat A, rmat B);
rmat mult(rmat A, rmat B);
rmat transposition(rmat A);
int inverse(rmat A, rmat invA);
float det(rmat A);
rmat getMinor(rmat matrix, int row, int col);
rmat pivot(rmat A);
void echLigne(rmat A, int row1, int row2, int coln);
int rang(rmat A);
float trace(rmat A);
float* valeurPropre(rmat A);
int dimEspacePropre(rmat A, float lamda);
void freeMatrix(rmat matrix);
#endif
