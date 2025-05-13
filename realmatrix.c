
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
        
    }}
    rmat add(rmat A, rmat B){
        int i,j;
        rmat C=init(A.rown,B.coln);
      
    if(A.coln!=B.coln || A.rown!=B.rown){
    printf("la somme des matrices A et B n'est pas definie ");}
    else{
        for(i=0;i<A.rown;i++){
            for(j=0;j<A.coln;j++){
                C.coeff[i][j]=A.coeff[i][j]+B.coeff[i][j];
                
            }


        }
    


    }
    return C;
    }
    rmat mult(rmat A, rmat B){
        rmat M=init(A.rown,B.coln);
        int i,j,k;
        float P=0;


        for ( i = 0; i < A.rown; i++)
        {
            for (j= 0; j< B.coln; j++)
            {
    for ( k = 0; k< A.coln; k++)
    {
        
        P=P+(A.coeff[i][k]*B.coeff[k][j]);
    }
    M.coeff[i][j]=P;
    P=0;
    

            }
            
        }
        return M;
        


    }
    rmat transposition(rmat A){
        int i,j;
        rmat T=init(A.coln,A.rown);
        for(i=0;i<A.rown;i++){
            for(j=0;j<A.coln;j++){
                T.coeff[j][i]=A.coeff[i][j];
            }
        }
        return T;



    }
    












    



