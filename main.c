#include <stdio.h>
#include <stdlib.h>
#include "realmatrix.h"


int main()
{
    int type;
    int ordre;
    int ligne, colonne;

    // Insertion du nmbre de colonnes et de lignes
    printf("Donner le nmbre de lignes:\n");
    scanf("%d",&ligne);
    printf("Donner le nmbre de colonnes:\n");
    scanf("%d",&colonne);

    rmat M=init(ligne,colonne);
    rmat N=init(ligne,colonne);
    rmat trans = init(colonne, ligne);
    rmat A=init(ligne,colonne);
    rmat invA=init(ligne, colonne);

    remplirMat(M);
    affiche(M);

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
        remplirMat(M);

        remplirMat(N);

        if (M.rown==N.coln)
        {
            A=mult(M,N);
            printf("Le resultat de la mult est:\n");
            affiche(A);
            if (M.coln==N.coln)
            {
                A=add(M,N);
                printf("Le resultat de l'add est:\n");
                affiche(A);
            }
        }
        else
        {
            printf("Pour une multiplication, il faut un nombre de colonne et de lign egal entre les deux matrice.\n");
        }
    }
    else if (type==2)
    {
        remplirMat(M);

        if (M.coln==M.rown)
        {
            printf("La matrice Identite de votre matrice est:\n");
            A=init_Id(M.coln);
            affiche(A);
            printf("\n");

            float determinant = det(M);
            printf("Le determinant de votre Matrice est: %f \n.", determinant); 

            printf("\n");

            printf("\n La matrice echelonne de votre matrice est:\n");
            A=pivot(M);
            affiche(A);

            type=trace(M);
            printf("La trace de ta Matricule est: %d.\n", type);

            printf("\n");

        }
        else
        {
            printf("Desole, votre matrice n'est pas carree.\n");
        }

        trans=transposition(M);
        printf("Le resultat de la transposition est:\n");
        affiche(trans);

        

        printf("\n");
        printf("L'inverse de votre matrice s'il existe est:\n");

        inverse(M,invA);
    }

    freeMatrix(M);
    freeMatrix(N);
    freeMatrix(A);
    freeMatrix(invA);
    return 0;
}