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

    // Test addition
    rmat C = add(A, B);
    printf("A + B:\n");
    affiche(C);
    free_matrix(C);
    
    // Test multiplication
    rmat D = mult(A, B);
    printf("A × B:\n");
    affiche(D);
    free_matrix(D);
    
    // Test transposée
    rmat T = transposition(A);
    printf("Transposée de A:\n");
    affiche(T);
    free_matrix(T);
    
    // Test trace
    printf("Trace de A: %.2f\n", trace(A));
    
    free_matrix(A);
    free_matrix(B);
}

    return 0;
    
