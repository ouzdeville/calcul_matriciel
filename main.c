#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"


int main()
{
    rmat A,B,C,P,T,invA;
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

   C=add(A,B);
    printf("C=\n");
    affiche(C);

    P=mult(A,B);
    printf("P=\n");
    affiche(P);

    T=transposition(A);
    printf("T=\n");
    affiche(T);
    A.coeff[0][0] = 1;
A.coeff[0][1] = 2;
A.coeff[1][0] = 3;
A.coeff[1][1] = 4;

    inverse(A, &invA);
    printf("invA =\n");
    affiche(invA);

    return 1;
}