#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"


int main()
{
    rmat A,B,C;
    A=init(2,2);
    B=init(2,2);
    int i,j;
    srand( time( NULL ) );
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            A.coeff[i][j]=((int)rand())%6;
            B.coeff[i][j]=((int)rand())%6;
        }
        
    }
   
    printf("A=\n");
    affiche(A);
    printf("B=\n");
    affiche(B);

    //appel fonction addition 
    C=add(A,B);
    printf("C=\n");
    affiche(C);
//appel fonction multiplication
    C=mult(A,B);
    printf("C=\n");
    affiche(C);
    //appelle de la fonction transposé
rmat At = transposition(A);
affiche(At);

int inverse(rmat A, rmat invA);
rmat invA = init(A.rown, A.coln); // ==> déclare et initialise invA !

if (inverse(A, invA)) {
    printf("Matrice inverse :\n");
    affiche(invA);
} else {
    printf("Inversion impossible.\n");
}
    float determinant = det(A);
    printf("Le déterminant de A est : %.2f\n", determinant);
    
}