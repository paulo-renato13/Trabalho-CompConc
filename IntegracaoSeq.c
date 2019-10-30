#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoes.h"
#include "timer.h"

int main(int argc, char * argv[]) {
	double inicio, fim, tempo; //Variaveis para medir o tempo decorrido
	float integral;
	GET_TIME(inicio); 
	float a = atof(argv[1]);
	float b = atof(argv[2]);
	float erro = atof(argv[3]);
	char funcao = *argv[4];
	integral = integracao_numerica(a, b, erro, funcao);
	printf("Valor aproximado da integral definida: %f\n", integral);
	GET_TIME(fim); 
	tempo = fim - inicio;
	printf("Tempo decorrido: %.5lf\n", tempo);
	return 0;
}
