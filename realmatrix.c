
#include <stdlib.h>
#include <stdio.h>
#include "realmatrix.h"



rmat init(int ligne, int colonne){

    rmat mat;
    int i=0;
    mat.rown=ligne;
    mat.coln=colonne;
    // je déclare un tableau contenant des tableaux (float *)
    // les lignes sont des tablaux de tablaux
    mat.coeff=(float **) malloc(mat.rown *sizeof(float *));
    for ( i = 0; i < mat.rown; i++)
    {
        // chaque ligne est un tableau de réel
        mat.coeff[i]= calloc(mat.coln, sizeof(float));
    }

    return mat;
}

rmat init_Id(int ordre){
    rmat mat;
    int i=0;
    mat=init(ordre, ordre);
     for ( i = 0; i < mat.rown; i++)
    {
        // chaque ligne est un tableau de réel
        mat.coeff[i][i]=1;
    }
    return mat;
}

void affiche(rmat A){
    int i,j;
    for ( i = 0; i < A.rown; i++)
    {
        for ( j = 0; j < A.coln; j++)
        {
            printf("%0.2f \t", A.coeff[i][j]);
        }
        printf("\n");
        
    }
    

}
rmat add(rmat A, rmat B){
    if (A.rown != B.rown || A.coln != B.coln){
        printf("\n addition impossible");
       
    }
    rmat C = init(A.rown, A.coln);
    for(int i=0; i<A.rown; i++){
        for(int j=0;j<A.coln;j++){
            C.coeff[i][j]=A.coeff[i][j] + B.coeff[i][j];
        }
    }
    return C;
}
rmat mult(rmat A, rmat B){
    if (A.coln != B.rown){
        printf("\n multiplication impossible");

    }
    rmat C= init(A.rown, B.coln);
    for(int i=0;i<A.rown;i++){
        for(int j=0;j<B.coln;j++){
        C.coeff[i][j]=0;
        for(int k=0;k<A.coln;k++){
            C.coeff[i][j] += A.coeff[i][k]*B.coeff[k][j];
        }
    }
}
return D;

}
rmat transposition(rmat A){
    rmat C = init(A.coln,A.rown);
    for (int i = 0; i < A.rown; i++){
        for (int  j = 0; j < A.coln; j++){
            C.coeff[j][i] = A.coeff[i][j];
        }
        

        
    }
    return C;
    

}
int inverse(rmat A){
    rmat invA;
    if (A.rown != A.coln){
        printf("\n Inversion impossible ");
    }
    int n = A.rown;
    invA=init(n,n);
    for (int i = 0; i < n; i++){
       for (int j = 0; j < n; j++)  {
        invA.coeff[i][j] = (i==j) ? 1.0 : 0.0;
       }  
    }
    for (int i = 0; i < n; i++) {
       double diag = A.coeff[i][i];
       if (diag ==0){
        printf("\n Inersion impossible pivot nul");

       }
       for (int j = 0; j < n; j++){
        A.coeff[i][j]/= diag;
        invA.coeff[i][j]/=diag;
       }
       for (int k = 0; k<n; k++){
       if (k!=i){
        double factor = A.coeff[k][i];
        for(int j =0;j<n;j++){
            A.coeff[k][j]-=factor * A.coeff[i][j];
            invA.coeff[k][j] -= factor * invA.coeff[i][j];
        }
       }
       }
    }
return invA;
}


float det(rmat A){


}



