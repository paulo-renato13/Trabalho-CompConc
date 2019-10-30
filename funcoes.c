//Implementação das funções básicas
#include "funcoes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Funções para os casos de teste
float funcA(float x) {
	return 1 + x;
}

float funcB(float x) {
	if(x <= -1 || x >= 1) { 
		printf("Entrada invalida!"); //Restrições de domínio
		exit(1);
	}
	return sqrt(1+pow(x,2));
}

float funcC(float x) {
	return sqrt(1+pow(x,4));
}

float funcD(float x) {
	return sin(pow(x,2));
}

float funcE(float x) {
	return cos(exp(-x));
}

float funcF(float x) {
	return cos(exp(-x))*x;
}

float funcG(float x) {
	return cos(exp(-x))*(0.005*pow(x,3)+1);
}

//Funcao para calcular a área dos retangulos
float area(tPonto ini, tPonto fim) {
	float area_calculada = (fim.coordX-ini.coordX)*fim.coordY;
	if (ini.coordX < 0 && fim.coordX > 0)  return -area_calculada;
	return area_calculada;
}

//Função recursiva que realiza a integracao numerica
float integracao_numerica(float a, float b, float erro, char funcao) {
	//Variaveis da funcao
	tPonto inicial, final, medio;
	float areaMaior, areaMenores, dif;
	//Calculo dos pontos
	inicial.coordX = a;
	final.coordX = b;
	switch (funcao){
		case 'A':
		inicial.coordY = funcA(a);
		final.coordY = funcA(b);
		break;
		case 'B':
		inicial.coordY = funcB(a);
		final.coordY = funcB(b);
		break;
		case 'C':
		inicial.coordY = funcC(a);
		final.coordY = funcC(b);
		break;
		case 'D':
		inicial.coordY = funcD(a);
		final.coordY = funcD(b);
		break;
		case 'F':
		inicial.coordY = funcF(a);
		final.coordY = funcF(b);
		break;
		case 'G':
		inicial.coordY = funcG(a);
		final.coordY = funcG(b);
		break;
	}
	medio.coordX = (inicial.coordX + final.coordX)/2;
	medio.coordY = (inicial.coordY + final.coordY)/2;
	//Calculo da area dos retangulos
	areaMaior = area(inicial, final);
	areaMenores = area(inicial, medio) + area(medio, final);
	//Verificacao da diferenca
	dif = areaMaior - areaMenores;
	if (dif < 0) dif = -dif;
	//Verificacao do erro
	if(dif<=erro) {
		return areaMaior;
	} else {
		return integracao_numerica(inicial.coordX, medio.coordX, erro, funcao)+integracao_numerica(medio.coordX, final.coordX, erro, funcao);
	}
}
