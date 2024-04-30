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
rmat add(rmat A, rmat B);
rmat mult(rmat A, rmat B);
rmat transposition(rmat A);
rmat inverse(rmat A);
float det(rmat A);
float trace(rmat A);
rmat pivot(rmat A);
int rang(rmat A);
float* valeurPropre(rmat A);
int dimEspacePropre(rmat A, float lamda);
#endif
