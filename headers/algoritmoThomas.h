#ifndef ALGORITMO_THOMAS_H_
#define ALGORITMO_THOMAS_H_

typedef struct coeficientes Coeficientes;

Coeficientes* inicializaCoeficientes(double **A, double *b, int n);

void decomposicao(Coeficientes *c, int n);

void substituicaoProgressiva(Coeficientes *c, int n);

void substituicaoRegressiva(Coeficientes *c, int n, double *x);

double* resolveSistema(double **A, double *b, int n);

void destroiCoeficientes(Coeficientes *c);

#endif
