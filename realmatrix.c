
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
        rmat C;
            /*int l = 3, n = 4;  // Dimensions : 3 lignes, 4 colonnes
            int A[3][4], B[3][4], C[3][4];
        
            // Saisie de la matrice A
            printf("Entrez les éléments de la matrice A (%d x %d) :\n", l, n);
            for (int i = 0; i < l; i++) {
                for (int j = 0; j < n; j++) {
                    printf("A[%d][%d] = ", i, j);
                    scanf("%d", &A[i][j]);
                }
            }
        
            // Saisie de la matrice B
            printf("\nEntrez les éléments de la matrice B (%d x %d) :\n", l, n);
            for (int i = 0; i < l; i++) {
                for (int j = 0; j < n; j++) {
                    printf("B[%d][%d] = ", i, j);
                    scanf("%d", &B[i][j]);
                }
        }*/
        if 
            // Addition A + B = C
        for (int i = 0; i < A.rown; i++) {
            for (int j = 0; j < A.coln; j++) {
            C.coeff[i][j] = A.coeff[i][j] + B.coeff[i][j];
            }
        }

        // Affichage du résultat
        printf("\nRésultat de l'addition (matrice C) :\n");
		    printf("\n");
		    printf("Matrice A :\n");
	    affiche(A);

	    printf("Matrice B :\n");
	    affiche(B);

	    printf("Résultat A + B = C :\n");
	    affiche(C);

        }
        //Multiplication de A * B = C 
        for (int i = 0; i < A.rown; i++) {
            for (int j = 0; j < B.coln; j++) {
             C.coeff[i][j] = 0;
             for (int k = 0; k < A.coln; k++) {
            C.coeff[i][j] += A.coeff[i][k] * B.coeff[k][j];
            }
        }
        //Affichage de C le resultat
         printf("\nRésultat de la multiplication (matrice C) :\n\n");         
		    printf("Matrice A :\n");
	    affiche(A);

	    printf("Matrice B :\n");
	    affiche(B);

	    printf("Résultat A + B = C :\n");
	    affiche(C);
	    
	//Determinant d'une matrice 
	    
	float determinant(rmat A, int n) {
	    if (n == 1)
		return A.coeff[0][0];
	    if (n == 2)
		return A.coeff[0][0] * A.coeff[1][1] - A.coeff[0][1] * A.coeff[1][0];
	    
	    float det = 0;
	    rmat temp;
	    temp = init(n - 1, n - 1);

	    for (int p = 0; p < n; p++) {
		int h = 0;
		int k = 0;
		for (int i = 1; i < n; i++) {
		    for (int j = 0; j < n; j++) {
		        if (j == p)
		            continue;
		        temp.coeff[h][k++] = A.coeff[i][j];
		        if (k == n - 1) {
		            k = 0;
		            h++;
		        }
		    }
		}
		det += pow(-1, p) * A.coeff[0][p] * determinant(temp, n - 1);
	    }
	    return det;
	    
	     // Affichage du résultat avec une précision de 2 décimales
	    cout << "Le déterminant de la matrice A est: " << fixed << setprecision(2) << det << endl;
	    
	    return 0;
		    
	    //inverse d'une matrice
            
	rmat inverser(rmat A, int n) {
	    float det = determinant(A, n);
	    if (det == 0) {
		printf("La matrice n'est pas inversible\n");
		exit(1);
	    }

	    // Calculer la matrice inverse (méthode fictive ici)
	    rmat inverse = /* votre méthode d'inversion ici */;

	    // Affichage de la matrice inverse
	    printf("Matrice inverse :\n");
	    afficherMatrice(inverse, n);

	    return inverse;
	}

        return 0;

    
  }

    

