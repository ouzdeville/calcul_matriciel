#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"


int main()
{
    rmat A,B,C,M,T;
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
    printf("C= A+B\n");
    affiche(C);

    M=mult(A,B);
    printf("M= A*B\n");
    affiche(M);

    T=transposition(A);
    printf("T la transposition de A\n");
    affiche(T);
    
    
    return 1;
}