#ifndef MATRIX_H
#define MATRIX_H

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

#endif