#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"


int main()
{
    rmat A,B,C,T;
    A=init(2,2);
    B=init(2,2);
    int i,j;
    srand( time( NULL ) );
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            A.coeff[i][j]=((int)rand())%2;
            B.coeff[i][j]=((int)rand())%2;
        }
        
    }

   
   
    printf("A=\n");
    affiche(A);
    printf("B=\n");
    affiche(B);

    C=mult(A,B);
    printf("C=\n");
    affiche(C);


     T = transposition(A);
    printf("Transpose de A=\n");
    affiche(T);
    
    

    float determinant = det(A);
    printf("Determinant de A = %0.2f\n", determinant);

    rmat P = pivot(A);
    printf("Matrice en forme échelonnée =\n");
    affiche(P);

   int M = rang(A);
    printf("Rang de A = %d\n", M);
    return 1;
}