#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"




int main()
{
    rmat A,B,C,invA;
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

  /* C=add(A,B);
    printf("C=\n");
    affiche(C);

    C=mult(A,B);
    printf("C=\n");
    affiche(C);

    C=transposition(A);
    printf("T=\n");
    affiche(T);*/

    invA=inverse(A);
    printf("invA=\n");
    affiche(invA);
    
   return 1;
}
