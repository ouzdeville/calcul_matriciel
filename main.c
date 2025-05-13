#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"

int main()
{
    rmat A, B, C, T;
    int i, j;

    // Demander les dimensions des matrices
    int rows, cols;
    printf("Entrez le nombre de lignes des matrices : ");
    scanf("%d", &rows);
    printf("Entrez le nombre de colonnes des matrices : ");
    scanf("%d", &cols);

    // Initialiser les matrices A et B
    A = init(rows, cols);
    B = init(rows, cols);

    // Demander à l'utilisateur de remplir la matrice A
    printf("Entrez les éléments de la matrice A :\n");
    for (i = 0; i < A.rown; i++) {
        for (j = 0; j < A.coln; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf("%f", &A.coeff[i][j]);
        }
    }

    // Demander à l'utilisateur de remplir la matrice B
    printf("Entrez les éléments de la matrice B :\n");
    for (i = 0; i < B.rown; i++) {
        for (j = 0; j < B.coln; j++) {
            printf("B[%d][%d] = ", i, j);
            scanf("%f", &B.coeff[i][j]);
        }
    }

    // Afficher les matrices A et B
    printf("Matrice A :\n");
    affiche(A);

    printf("Matrice B :\n");
    affiche(B);

    // Additionner les matrices A et B
    C = add(A, B);

    // Afficher la matrice résultat C
    printf("Matrice C (A + B) :\n");
    affiche(C);

  // Multiplier les matrices A et B
   C = mult(A, B);

   // Afficher la matrice résultat 
   printf("Matrice C (A * B) :\n");
     affiche(C);


    // Calculer la transposée de la matrice A
    T = transposition(A);

    // Afficher la matrice transposée T
    printf("Matrice T (transposée de A) :\n");
    affiche(T);

    rmat invA;
    
    

    // Demander la taille de la matrice carrée
    printf("Entrez la taille de la matrice carrée : ");
    int n;
    scanf("%d", &n);

    // Initialiser les matrices A et invA
    A = init(n, n);
    invA = init(n, n);

    

    // Afficher la matrice A
    printf("Matrice A :\n");
    affiche(A);

    // Calculer l'inverse de A
    if (inverse(A, invA)) {
        // Afficher la matrice inverse
        printf("Matrice inverse de A :\n");
        affiche(invA);
    } else {
        // Si la matrice n'est pas inversible
        printf("La matrice A n'est pas inversible.\n");
    }

    // Calculer le déterminant de A
    float determinant = det(A);
    printf("Le déterminant de la matrice A est : %0.2f\n", determinant);
   // Calculer la trace de A
   float tr = trace(A);
   printf("La trace de la matrice A est : %0.2f\n", tr);
   //calculer rmat pivot(rmat A)
   rmat P = pivot(A);
   printf("Matrice P (matrice échelonnée de A) :\n");
   affiche(P);
    // Calculer le rang de A
    int rank = rang(A);
    printf("Le rang de la matrice A est : %d\n", rank);
    // Calculer les valeurs propres de A
    return 0;

}



/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realmatrix.h"

// Fonction pour afficher le menu
void afficher_menu() {
    printf("\n=== MENU ===\n");
    printf("1. Additionner deux matrices\n");
    printf("2. Multiplier deux matrices\n");
    printf("3. Calculer la transposée d'une matrice\n");
    printf("4. Calculer l'inverse d'une matrice\n");
    printf("5. Calculer le déterminant d'une matrice\n");
    printf("6. Calculer la trace d'une matrice\n");
    printf("7. Calculer la matrice échelonnée (pivot de Gauss)\n");
    printf("8. Quitter\n");
    printf("Choisissez une option : ");
}

int main() {
    rmat A, B, C, T, invA, P;
    int i, j, choix;
    int rows, cols;

    while (1) {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1: // Additionner deux matrices
                printf("Entrez le nombre de lignes des matrices : ");
                scanf("%d", &rows);
                printf("Entrez le nombre de colonnes des matrices : ");
                scanf("%d", &cols);

                A = init(rows, cols);
                B = init(rows, cols);

                printf("Entrez les éléments de la matrice A :\n");
                for (i = 0; i < A.rown; i++) {
                    for (j = 0; j < A.coln; j++) {
                        printf("A[%d][%d] = ", i, j);
                        scanf("%f", &A.coeff[i][j]);
                    }
                }

                printf("Entrez les éléments de la matrice B :\n");
                for (i = 0; i < B.rown; i++) {
                    for (j = 0; j < B.coln; j++) {
                        printf("B[%d][%d] = ", i, j);
                        scanf("%f", &B.coeff[i][j]);
                    }
                }

                C = add(A, B);
                printf("Matrice C (A + B) :\n");
                affiche(C);
                // liberer_memoire(A);
                // liberer_memoire(B);
                // liberer_memoire(C);
                break;

            case 2: // Multiplier deux matrices
                printf("Entrez le nombre de lignes de la matrice A : ");
                scanf("%d", &rows);
                printf("Entrez le nombre de colonnes de la matrice A : ");
                scanf("%d", &cols);

                A = init(rows, cols);

                printf("Entrez le nombre de colonnes de la matrice B : ");
                int colsB;
                scanf("%d", &colsB);

                B = init(cols, colsB);

                printf("Entrez les éléments de la matrice A :\n");
                for (i = 0; i < A.rown; i++) {
                    for (j = 0; j < A.coln; j++) {
                        printf("A[%d][%d] = ", i, j);
                        scanf("%f", &A.coeff[i][j]);
                    }
                }

                printf("Entrez les éléments de la matrice B :\n");
                for (i = 0; i < B.rown; i++) {
                    for (j = 0; j < B.coln; j++) {
                        printf("B[%d][%d] = ", i, j);
                        scanf("%f", &B.coeff[i][j]);
                    }
                }

                C = mult(A, B);
                printf("Matrice C (A * B) :\n");
                affiche(C);
                // liberer_memoire(A);
                // liberer_memoire(B);
                // liberer_memoire(C);
                break;

            case 3: // Calculer la transposée d'une matrice
                printf("Entrez le nombre de lignes de la matrice : ");
                scanf("%d", &rows);
                printf("Entrez le nombre de colonnes de la matrice : ");
                scanf("%d", &cols);

                A = init(rows, cols);

                printf("Entrez les éléments de la matrice A :\n");
                for (i = 0; i < A.rown; i++) {
                    for (j = 0; j < A.coln; j++) {
                        printf("A[%d][%d] = ", i, j);
                        scanf("%f", &A.coeff[i][j]);
                    }
                }

                T = transposition(A);
                printf("Matrice T (transposée de A) :\n");
                affiche(T);
                // liberer_memoire(A);
                // liberer_memoire(T);
                break;

            case 4: // Calculer l'inverse d'une matrice
                printf("Entrez la taille de la matrice carrée : ");
                scanf("%d", &rows);

                A = init(rows, rows);
                invA = init(rows, rows);

                printf("Entrez les éléments de la matrice A :\n");
                for (i = 0; i < A.rown; i++) {
                    for (j = 0; j < A.coln; j++) {
                        printf("A[%d][%d] = ", i, j);
                        scanf("%f", &A.coeff[i][j]);
                    }
                }

                if (inverse(A, invA)) {
                    printf("Matrice inverse de A :\n");
                    affiche(invA);
                } else {
                    printf("La matrice A n'est pas inversible.\n");
                }
                // liberer_memoire(A);
                // liberer_memoire(invA);
                break;

            case 5: // Calculer le déterminant d'une matrice
                printf("Entrez la taille de la matrice carrée : ");
                scanf("%d", &rows);

                A = init(rows, rows);

                printf("Entrez les éléments de la matrice A :\n");
                for (i = 0; i < A.rown; i++) {
                    for (j = 0; j < A.coln; j++) {
                        printf("A[%d][%d] = ", i, j);
                        scanf("%f", &A.coeff[i][j]);
                    }
                }

                float determinant = det(A);
                printf("Le déterminant de la matrice A est : %0.2f\n", determinant);
                // liberer_memoire(A);
                break;

            case 6: // Calculer la trace d'une matrice
                printf("Entrez la taille de la matrice carrée : ");
                scanf("%d", &rows);

                A = init(rows, rows);

                printf("Entrez les éléments de la matrice A :\n");
                for (i = 0; i < A.rown; i++) {
                    for (j = 0; j < A.coln; j++) {
                        printf("A[%d][%d] = ", i, j);
                        scanf("%f", &A.coeff[i][j]);
                    }
                }

                float tr = trace(A);
                printf("La trace de la matrice A est : %0.2f\n", tr);
                // liberer_memoire(A);
                break;

            case 7: // Calculer la matrice échelonnée
                printf("Entrez le nombre de lignes de la matrice : ");
                scanf("%d", &rows);
                printf("Entrez le nombre de colonnes de la matrice : ");
                scanf("%d", &cols);

                A = init(rows, cols);

                printf("Entrez les éléments de la matrice A :\n");
                for (i = 0; i < A.rown; i++) {
                    for (j = 0; j < A.coln; j++) {
                        printf("A[%d][%d] = ", i, j);
                        scanf("%f", &A.coeff[i][j]);
                    }
                }

                P = pivot(A);
                printf("Matrice P (matrice échelonnée de A) :\n");
                affiche(P);
                // liberer_memoire(A);
                // liberer_memoire(P);
                break;

            case 8: // Quitter
                printf("Au revoir !\n");
                exit(0);

            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}*/