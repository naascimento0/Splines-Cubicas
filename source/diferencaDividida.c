#include <stdlib.h>
#include <stdio.h>
#include "../headers/diferencaDividida.h"

/* Cria-se a matriz de diferenças divididas */
double** processaDiferencaDividida(int n, double *x, double *y){
	double **dd = calloc(n, sizeof(double*));
	for(int i = 0; i < n; i++){
		dd[i] = calloc(n, sizeof(double));
		dd[i][0] = y[i];
	}

	for(int k = 1; k < n; k++){
		for(int i = 0; i < n - k; i++)
			dd[i][k] = (dd[i + 1][k - 1] - dd[i][k - 1]) / (x[i + k] - x[i]);
	}

	return dd;
}

void destroiMatrizDiferencaDividida(double **diferencaDividida, int n){
	for(int i = 0; i < n; i++)
		free(diferencaDividida[i]);
	free(diferencaDividida);
}

/* Cria-se  o vetor 'b' do sistema linear Hu = b */
double* criaVetorDiferencaDividida(int n, double *x, double *y){
	double **diferencaDividida = processaDiferencaDividida(n, x, y);

	double *vetor = calloc(n - 2, sizeof(double));
	for(int i = 1; i < n - 1; i++)
		vetor[i - 1] = 6 * (diferencaDividida[i][1] - diferencaDividida[i - 1][1]);

	destroiMatrizDiferencaDividida(diferencaDividida, n);
	return vetor;
}
