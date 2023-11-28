#include <stdio.h>
#include <stdlib.h>

#include "headers/algoritmoThomas.h"
#include "headers/diferencaDividida.h"
#include "headers/matrizH.h"
#include "headers/polinomios.h"

void processaEntrada(int *n, double **x, double **y, double *z, int *m){
	printf("Digite a quantidade de pontos: \n");
	scanf("%d", n);

	if(*n < 3)
		exit(printf("Erro: n deve ser maior ou igual a 3\n"));

	printf("\nDigite a lista de valores de x, separados por espaço: \n");
	*x = calloc(*n, sizeof(double));
	for(int i = 0; i < *n; i++)
		scanf("%lf", &(*x)[i]);

	printf("\nDigite a lista de valores de y, separados por espaço: \n");
	*y = calloc(*n, sizeof(double));
	for(int i = 0; i < *n; i++)
		scanf("%lf", &(*y)[i]);

	printf("\nDigite o valor de z: \n");
	scanf("%lf", z);

	printf("\nDigite o valor de m: \n");
	scanf("%d", m);
}

void mostraEntrada(int n, double *x, double *y, double z, int m){
	printf("\nn = %d\n\n", n);

	printf("x = ");
	for(int i = 0; i < n; i++)
		printf("%.2lf ", x[i]);

	printf("\n\ny = ");

	for(int i = 0; i < n; i++)
		printf("%.2lf ", y[i]);

	printf("\n\nz = %.2lf\n", z);

	printf("\nm = %d\n", m);
}

int main(){
	int n;
	double *x, *y;
	double z;
	int m;
	processaEntrada(&n, &x, &y, &z, &m);
	//mostraEntrada(n, x, y, z, m);

	double **H = criaMatrizH(n, x, y);

	double *vetorDiferencaDividida = criaVetorDiferencaDividida(n, x, y);

	double *segundasDerivadas = resolveSistema(H, vetorDiferencaDividida, n);

	Polinomios *p = criaPolinomios(segundasDerivadas, x, y, n);

	//mostraPolinomios(p);

	printf("\nPara o valor de z = %lf, sua imagem na spline é = %lf\n\n", z, interpolaValorZ(p, z));

	mostraConjuntoMPontos(p, m);

	free(x), free(y);
	free(vetorDiferencaDividida);
	for(int i = 0; i < n - 2; i++)
		free(H[i]);
	free(H);
	free(segundasDerivadas);
	destroiPolinomios(p);

	return 0;
}



