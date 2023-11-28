#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../headers/polinomios.h"

struct polinomios{
	double *a, *b, *c, *d;
	int qtdPolinomios;
	double *x;
};

/* Funcao que calcula os coeficientes a, b, c e d dos polinomios da spline cubica */
Polinomios* criaPolinomios(double *segundasDerivadas, double *x, double *y, int n){
	Polinomios *p = malloc(sizeof(Polinomios));
	p->a = calloc(n - 1, sizeof(double));
	p->b = calloc(n - 1, sizeof(double));
	p->c = calloc(n - 1, sizeof(double));
	p->d = calloc(n - 1, sizeof(double));
	p->qtdPolinomios = n - 1;
	p->x = x;

	for(int i = 0; i < n - 1; i++){
		double h = x[i + 1] - x[i];
		double dd = (y[i + 1] - y[i]) / h;
		p->a[i] = (segundasDerivadas[i + 1] - segundasDerivadas[i]) / (6.0 * h);
		p->b[i] = segundasDerivadas[i] / 2.0;
		p->c[i] = dd - ((segundasDerivadas[i + 1] + 2.0 * segundasDerivadas[i]) * h / 6.0);
		p->d[i] = y[i];
	}

	return p;
}

/* Funcao que mostra os polinomios da spline cubica*/
void mostraPolinomios(Polinomios *p){
	for(int i = 0; i < p->qtdPolinomios; i++){
		printf("%d° polinomio: %lf(x - xi)³ + %lf(x - xi)² + %lf(x - xi) + %lf\n", i, p->a[i], p->b[i], p->c[i], p->d[i]);
	}
}

void destroiPolinomios(Polinomios *p){
	free(p->a), free(p->b), free(p->c), free(p->d);
	free(p);
}

/* Funcao para retornar o valor da imagem de qualquer ponto z na spline cubica */
double interpolaValorZ(Polinomios *p, double z){
	if(z < p->x[0] || z > p->x[p->qtdPolinomios])
		exit(printf("Erro: valor z fora do escopo do domínio"));

	double xi;
	int i;
	for(i = 0; i < p->qtdPolinomios; i++){
		if(z >= p->x[i] && z <= p->x[i + 1]){
			xi = p->x[i];
			break;
		}
	}

	return (p->a[i] * pow(z - xi, 3)) + (p->b[i] * pow(z - xi, 2)) + (p->c[i] * (z - xi)) + p->d[i];
}

/* Funcao para gerar as imagens das splines para um conjunto de m pontos dentro do dominio */
void mostraConjuntoMPontos(Polinomios *p, int m){
	double espacamento = fabs(p->x[p->qtdPolinomios] - p->x[0]) / m;

	double *x = calloc(m + 1, sizeof(double));
	double *y = calloc(m + 1, sizeof(double));
	double count = p->x[0];

	int i = 0;
	for(i = 0; i < m; i++){
		y[i] = interpolaValorZ(p, count);
		x[i] = count;
		count += espacamento;
	}

	y[i] = interpolaValorZ(p, p->x[p->qtdPolinomios]);
	x[i] = p->x[p->qtdPolinomios];

	printf("Valores de xi e suas respectivas imagens si(x) no conjunto de m pontos, igualmente espaçados:\n");
	for(int i = 0; i < m + 1; i++){
		printf("{%lf, %lf}\n", x[i], y[i]);
	}
	printf("\n\n");

	plotarGraficoMPontos(m + 1, x, y);

	free(x), free(y);
}

/* Plota o grafico dos m pontos utilizando o software gnuplot */
void plotarGraficoMPontos(int n, double *x, double *y){

    FILE *file = fopen("grafico.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para salvar dados.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
        fprintf(file, "%lf %lf\n", x[i], y[i]);

    fclose(file);
    system("gnuplot -persist -e \"plot 'grafico.txt' with linespoints title 'Pontos'\"");
}

