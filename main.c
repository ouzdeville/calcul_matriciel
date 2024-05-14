#include <stdio.h>
#include <stdlib.h>
#include "realmatrix.h"


int main()
{
    int type;
    int ordre;
    int ligne, colonne;

    //Insertion du nmbre de colonnes et de lignes
    printf("Donner le nmbre de lignes:\n");
    scanf("%d",&ligne);
    printf("Donner le nmbre de colonnes:\n");
    scanf("%d",&colonne);

    rmat M=init(ligne,colonne);
    rmat N=init(ligne,colonne);
    rmat A=init(ligne,colonne);

    printf("Quel type d'operation voulez vous faire?\n - 1 entre deux matrice \n - 2 sur une matrice.\n");
    do
    {
        printf("Entrez votre choix:\n");
        scanf("%d", &type);

        if (type != 1 && type != 2)
        {
            printf("Le choix est entre 1 et 2.\n");
        }
        
    } while (type != 1 && type !=  2);

    if (type == 1)
    {
        printf("Remplissage de M1:\n");
        for (int i = 0; i < M.rown; i++)
        {
            for (int j = 0; j < M.coln; j++)
            {
                printf("Entrez le coefficient %d%d de votre premiere matrice:", i,j);
                scanf("%f", &M.coeff[i][j]);
            }
        }

        printf("Remplissage de M2:\n");
        for (int i = 0; i < N.rown; i++)
        {
            for (int j = 0; j < N.coln; j++)
            {
                printf("Entrez le coefficient %d%d de votre premiere matrice:", i,j);
                scanf("%f", &N.coeff[i][j]);
            }
        }

        if (M.rown==M.coln)
        {
            A=mult(M,N);
            printf("Le resultat de la mult est:\n");
            affiche(A);
            A=add(M,N);
            printf("Le resultat de l'add est:\n");
            affiche(A);
        }
        else
        {
            printf("Le resultat de l'add est:\n");
            A = add(M,N);
            affiche(A);
        }
    }
    else if (type==2)
    {
        for (int i = 0; i < M.rown; i++)
        {
            for (int j = 0; j < M.coln; j++)
            {
                printf("Entrez le coefficient %d%d de votre premiere matrice:", i,j);
                scanf("%f", &M.coeff[i][j]);
            }
        }

        if (M.coln==M.rown)
        {
        printf("La matrice Identite de votre matrice est:\n");
        A=init_Id(M.coln);
        affiche(A);
        }

        M=transposition(M);
        printf("Le resultat de la transposition est:\n");
        affiche(M);

        // type=trace(M);
        // printf("La trace de ta Matricule est: %d.\n", type);
    }


    return 1;
}