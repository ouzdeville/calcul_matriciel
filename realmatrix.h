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

#endif