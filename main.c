#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"


int main()
{
    rmat A,B,C,D,T,invA;
    float detA;
    A=init(2,2);
    B=init(2,2);
    int i,j;
    srand( time( NULL ) );
    for ( i = 0; i < A.rown; i++){
        for ( j = 0; j < A.coln; j++){
            A.coeff[i][j]=((int)rand())%6;
            B.coeff[i][j]=((int)rand())%6;
        }
        
    }
   
    printf("Voici la matrice A : \n");
    affiche(A);
    printf("Voici la matrice B : \n");
    affiche(B);

    C=add(A,B);
    printf("Voici l'addition des matrices A et B\n");
    affiche(C);

    D=mult(A,B);
    printf("Voici la multiplication des matrices A et B\n");
    affiche(D);
    
    T=transposition(A);
    printf("Voici la transposition de la matrice A\n");
    affiche(T);

    detA=det(A);
    printf("Voici le determinant de la matrice A\n");
    printf("%f\n",detA);

    invA=inverse(A);
    printf("Voici l'inverse de la matrice A\n");
    affiche(invA);
    
    return 1;
}