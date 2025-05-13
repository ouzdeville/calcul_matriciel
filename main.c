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

    C=add(A,B);
    printf("C=\n");
    affiche(C);*/
   
    C = mult(A, B);
    printf("C = A * B =\n");
    affiche(C);

    C = transposition(A);
    printf("Transposée de A :\n");
    affiche(C);

   
    
    free(C.coeff);
    trace_matrice = trace(A);
    printf("la trace est:\t");
    affiche(trace_matrice);

    det = determinant(A);
    printf("le determinant est:\t");
    affiche(det);
    
    C = inverse(A, invA);
    affiche(C);
    
    
    return 1;
}