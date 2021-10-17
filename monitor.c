#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>

#include "monitor.h"


sem_t Mutex;
sem_t Proximo;

//conta no sem_t Proximo
int prox_sinal=0;

struct monitor_datatype{
	sem_t semaforo;
	int contador;

};
typedef struct monitor_datatype monitor_data;

monitor_data x[NUMERO_FILOSOFOS];
int estado[NUMERO_FILOSOFOS]; //ja declarado antes
int ciclo[NUMERO_FILOSOFOS];

//lembrar que as 2 principais funcoes de um monitor sao wait e signal

void wait(int i){
	//oque esta acontecendo:
	//pego a lista de filosofos e checo o proximo
	x[i].contador++;
	//se o sinal for positivo, uso o semaforo Proximo
	if(prox_sinal>0) {
		sem_post(&Proximo);
	}
	//caso contrario, uso o Mutex
	else {
		sem_post(&Mutex);
	}
	//espero o semaforo
	sem_wait(&x[i].semaforo);
	//retorno a posicao do contador
	x[i].contador--;
	
}

void signal(int i){
	//verificar o contador dentro do monitor
	if(x[i].contador>0){
		//apos isso subir o sinal
		prox_sinal++;
		sem_post(&x[i].semaforo);
		sem_wait(&Proximo);
		//apos realizar as operacoes, liberar o sinal
		prox_sinal--;
	}
}

void testar(int i){
	if(estado[i]==FOME && estado[ESQUERDA] != COMENDO && estado[DIREITA] != COMENDO && ciclo[i] == i && ciclo[ESQUERDA] == i){
	estado[i]=COMENDO;
	//mando o sinal que este esta comendo
	signal(i);
	}
}


void pegar_talher(int i){
	//segurar o mutex
	sem_wait(&Mutex);
	//mudo o estado 
	
	estado[i]=FOME;
	testar(i);
	//jogo o filosofo no teste para ver se ele pode comer
	while(estado[i]==FOME){
		//aqui espera ate liberar
		wait(i);
	}
	if(prox_sinal>0){
		//se tiver sinal, joga para o proximo semafoto
		sem_post(&Proximo);
	}
	else{
		//cc, Mutex
		sem_post(&Mutex);
	}
	

}
void soltar_talher(int i){
	//entro no estado critico	
	sem_wait(&Mutex);
	estado[i]=PENSANDO;
	//mudar o ciclo
	//Avanço em 1 unidade na mesa
	ciclo[i]=DIREITA;
	//E coloco o ciclo anterior apontando para a esqueda do prox;
	ciclo[ESQUERDA]=ESQUERDA;
	
	//apos isso testar a posicao
	testar(ESQUERDA);
	testar(DIREITA);
	
	if(prox_sinal>0){
		//se tiver sinal, joga para o proximo semafoto
		sem_post(&Proximo);
	}
	else{
		//cc, Mutex
		sem_post(&Mutex);
	}
	
	
}	
void iniciar(){

	int i;
	//iniciar os semaforos	
	sem_init(&Mutex,0,1);
	sem_init(&Proximo,0,0);
	//setar variaveis
	for(i=0;i<NUMERO_FILOSOFOS;i++){
		estado[i]=PENSANDO;
		sem_init(&x[i].semaforo,0,0);
		x[i].contador =0;
		ciclo[i]=i;
	}
	
	
	ciclo[1] = 2;
	ciclo[3] = 4;
	ciclo[6] = 0;

}
	






