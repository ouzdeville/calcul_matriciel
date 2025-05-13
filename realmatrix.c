
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
rmat add(rmat A, rmat B) {
int i,j;
if (A.rown != B.rown || A.coln != B.coln){
printf("Addition impossible\n");
}
rmat C = init(A.rown, A.coln);
for(i=0;i<A.rown;i++){
for(j=0;j<A.coln;j++){
C.coeff[i][j]=A.coeff[i][j] + B.coeff[i][j];
}
}
return C;
}
rmat mult(rmat A, rmat B){
int i,j,k;
if(A.coln != B.rown){
printf("Multiplication impossible");
}
rmat C =init(A.coln, B.rown);

for(i=0;i<A.rown;i++){
for(j=0;j<A.coln;j++){
for(k=0;i<A.coln;k++){
C.coeff[i][j]=A.coeff[i][k] * B.coeff[k][j];
}
}
}
return C;
}
/*rmat transposition(rmat A){
int i,j;
rmat C = init(A.coln,A.rown);
for(i=0;i<A.rown;i++){
for(j=0;j<A.coln;j++){
C.coeff[i][j]=A.coeff[j][i];
}
}
return C;
}*/
float trace(rmat A){
int i,j;
float trace_matrice;
trace_matrice=A.coeff[0][0];
for(i=0;i<A.rown;i++){
for(j=0;j<A.coln;j++){
trace_matrice=trace_matrice+A.coeff[i+1][j+1];
}
}

printf("la trace est egale a: %f",trace_matrice);

return trace_matrice;
}
float det(rmat A){
int i,j;
float determinant;
int colonne = 1;
int ligne = 1;
for(i=0;i<A.rown;i++){
for(j=0;j<A.coln;j++){
ligne += i;
colonne += j;
if(ligne != colonne){
printf("Impossible de calculer le determinant");
}else{
if(ligne ==2 || colonne==2){
determinant= (A.coeff[0][0] * A.coeff[1][1]) - (A.coeff[0][1] * A.coeff[1][0]);
}else{
printf("on peut calculer le determinant en utilisant les sous matrices");
//determinant = (-1)^(0+0) * A.coeff[0][0] * ;
//for(i=0;i<A.rown;i++){
//for(j=0;j<A.coln;j++){
//determinant += (-1)^(i+j) * A.coeff[i][j];
//}
//}
}
}
}
}

}
int inverse(rmat A, rmat invA){
int i,j;
float determinant;
printf("Entrez le determinant:");
scanf("%f",&determinant);
if(determinant==0){
printf("La matrice n'est pas inversible");
}else {
printf("l'expression suivante est la formule de l'inverse d'une matrice et de plus comA est la matrice des cofacteurs");
invA = (1/determinant) * (transposition(comA));
}
return invA;
}

