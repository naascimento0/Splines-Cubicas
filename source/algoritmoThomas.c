#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/algoritmoThomas.h"

struct coeficientes{
	double *e, *f, *g, *r;
};

/* Pega-se a matriz H e o vetor b e criam-se os coeficientes e, f, g e r. Este processo é necessário no algoritmo de Thomas para resolver sistemas tridiagonais */
Coeficientes* inicializaCoeficientes(double **A, double *b, int n){
	Coeficientes *c = malloc(sizeof(Coeficientes));
	c->e = calloc(n, sizeof(double));
	c->f = calloc(n, sizeof(double));
	c->g = calloc(n, sizeof(double));
	c->r = calloc(n, sizeof(double));

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j)
				c->f[i] = A[i][j];
			else if(j == i - 1)
				c->e[i] = A[i][j];
			else if(j == i + 1)
				c->g[i] = A[i][j];
		}
	}

	memcpy(c->r, b, n * sizeof(double));
	return c;
}

/* Processo de decomposicao do algoritmo de Thomas para resolver sistemas tridiagonais*/
void decomposicao(Coeficientes *c, int n){
	for(int k = 1; k < n; k++){
		c->e[k] /= c->f[k - 1];
		c->f[k] -= c->e[k] * c->g[k - 1];
	}
}

/* Processo de substituicao progressiva do algoritmo de Thomas para resolver sistemas tridiagonais */
void substituicaoProgressiva(Coeficientes *c, int n){
    for(int k = 1; k < n; k++)
        c->r[k] -= c->e[k] * c->r[k - 1];
}

/* Processo de substituicao regressiva do algoritmo de Thomas para resolver sistemas tridiagonais */
void substituicaoRegressiva(Coeficientes *c, int n, double *x){
    x[n - 1] = c->r[n - 1] / c->f[n - 1];
    for(int k = n - 2; k >= 0; k--)
        x[k] = (c->r[k] - c->g[k] * x[k + 1]) / c->f[k];
}

double* resolveSistema(double **A, double *b, int n){
	Coeficientes *c = inicializaCoeficientes(A, b, n - 2);

	double *x = calloc(n, sizeof(double));

	decomposicao(c, n - 2);
	substituicaoProgressiva(c, n - 2);
	substituicaoRegressiva(c, n - 2, x);

    for(int i = n - 1; i > 0; i--){
    	x[i] = x[i - 1];
    }

	x[0] = 0;
	x[n - 1] = 0;

	destroiCoeficientes(c);
	return x;
}

void destroiCoeficientes(Coeficientes *c){
	free(c->e), free(c->f),free(c->g),free(c->r);
	free(c);
}
