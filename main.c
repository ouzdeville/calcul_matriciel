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
            A.coeff[i][j]=((int)rand())%2;
            B.coeff[i][j]=((int)rand())%2;
        }
        
    }

    printf("A=\n");
    affiche(A);
    printf("B=\n");
    affiche(B);  

    /*C=mult(A,B);
    printf("C=\n");
    affiche(C); */

    C = add(A, B);
    printf("C = A + B =\n");
    affiche(C);

 C = mult(A, B);
    printf("C=\n");
    affiche(C);
    
   rmat T = transposition(A);
    printf("Transposee de A =\n");
    affiche(T);
    return 1;

    rmat inv = init(2,2);
    printf("Inverse de A :\n");
    if(inverse(A, inv)) {
        affiche(inv);
    }else {
        printf("Matrice non inversible.\n");
    }


float d = det(A);
printf("Determinant de A : %.2f\n", d);
}
