#include <stdlib.h>
#include <stdio.h>
#include "../headers/matrizH.h"

/* Cria-se um vetor de hi's, onde hi = x[i + 1] - x[i] */
double* criaVetorh(int n, double *x){
	double *h = calloc(n - 1, sizeof(double));
	for(int i = 0; i < n - 1; i++)
		h[i] = x[i + 1] - x[i];
	return h;
}

/* Cria-se o sistema triangular H a partir dos valores de x da entrada */
double** criaMatrizH(int n, double *x, double *y){
	double *h = criaVetorh(n, x);
	double **H = calloc(n - 2, sizeof(double**));

	for(int i = 0; i < n - 2; i++){
		H[i] = calloc(n - 2, sizeof(double));
		for(int j = 0; j < n - 2; j++){
			if(i == j)
				H[i][j] = 2 * (h[i] + h[i + 1]);
			else if(j == i - 1)
				H[i][j] = h[1];
			else if(j == i + 1)
				H[i][j] = h[i + 1];
		}
	}

	free(h);
	return H;
}
