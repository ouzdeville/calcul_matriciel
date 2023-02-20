#include <stdio.h>
#include <stdlib.h>
#include "realmatrix.h"


int main()
{
    int ligne, colonne;
    printf("Donner le nmbre de lignes");
    scanf("%d",&ligne);
    printf("Donner le nmbre de colonnes");
    scanf("%d",&colonne);
    rmat M=init(ligne,colonne);
    affiche(M);
    
    return 1;
}