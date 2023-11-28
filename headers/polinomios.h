#ifndef POLINOMIOS_H_
#define POLINOMIOS_H_

typedef struct polinomios Polinomios;

Polinomios* criaPolinomios(double *segundasDerivadas, double *x, double *y, int n);

void mostraPolinomios(Polinomios *p);

void destroiPolinomios(Polinomios *p);

double interpolaValorZ(Polinomios *p, double z);

void mostraConjuntoMPontos(Polinomios *p, int m);

void plotarGraficoMPontos(int n, double *x, double *y);

#endif
