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
    affiche(A);
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            int tmp;
            printf("\n Entrer les coefficients de A a la position \n i:%d \nj:%d : ",i,j);
            scanf("%d",&tmp);
            A.coeff[i][j] = tmp;
            // A.coeff[i][j]=((int)rand())%2;
            // B.coeff[i][j]=((int)rand())%2;
        }
        
    }
   
    printf("A=\n");
    affiche(A);
    // printf("B=\n");
    // affiche(B);

    // C=add(A,B);
    // printf("C=\n");
    // affiche(C);
    
    
    return 1;
}