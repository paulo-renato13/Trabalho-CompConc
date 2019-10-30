#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "funcoes.h"
#include "timer.h"

float integral; 
int nthreads;
float a, b, erro, bloco, intervalo;
char funcao;
pthread_mutex_t mutex;

//Funcao que realiza a integração concorrente
void *integracao_numericaConc(void *id_thread) {
	int id = * (int *) id_thread;
	float inicio, fim, integralTemp;
	//Calcula tamanho dos blocos
	inicio = a + id*bloco;
	fim = inicio + bloco;
	//Variavel temporaria para guardar o valor da integral no bloco
	integralTemp = integracao_numerica(inicio, fim, erro, funcao);
	//Seção crítica
	pthread_mutex_lock(&mutex);
	integral+=integralTemp;
	pthread_mutex_unlock(&mutex);
	//Finalização
	free(id_thread);
	pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
	pthread_t *tid_sistema; //Identificadores das threads
	int t; //Contador
	int *id_thread; //Identificador da thread
	double inicio, fim, tempo; //Variaveis para medir o tempo decorrido
	
	GET_TIME(inicio); 
	
	//Recebendo os argumentos
	a = atof(argv[1]);
	b = atof(argv[2]);
	erro = atof(argv[3]);
	nthreads = atoi(argv[4]);
	funcao = *argv[5];
	
	//Cálculo dos intervalos
	intervalo = b - a;
    bloco = intervalo/nthreads;
	
	//Alocação do vetor de nthreads
	tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);

	if(tid_sistema==NULL) {
    printf("--ERRO na MALLOC\n"); exit(-1);
	}
    
    //Inicialização do mutex
	pthread_mutex_init(&mutex, NULL);
    
    //Criacao das threads
	for(t=0; t<nthreads; t++) {
		id_thread = malloc(sizeof(int)); if(id_thread==NULL) { printf("--ERRO no MALLOC\n"); exit(-1); }
		*id_thread = t;
		if (pthread_create(&tid_sistema[t], NULL, integracao_numericaConc, (void*) id_thread)) {
		   printf("--ERRO na CRIACAO DAS THREADS\n"); exit(-1);
		}
	}

    //Join para finalização das threads
	for(t=0; t<nthreads; t++) {
		if (pthread_join(tid_sistema[t], NULL)) {
			printf("--ERRO no JOIN\n"); exit(-1);
		}
	}
    
	//Calculo do tempo e encerrado das funcoes
    printf("Valor aproximado da integral definida: %f\n", integral);
    GET_TIME(fim);
	tempo = fim - inicio;
	printf("Tempo decorrido com %d threads: %.5lf\n", nthreads, tempo);
    
    //Encerrado da thread da main
	pthread_exit(NULL);
	pthread_mutex_destroy(&mutex);
	
	return 0;
  }


