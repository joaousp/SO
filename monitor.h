//Aqui sera feito a declaração das variaveis e da biblioteca de funções

#ifndef monitor_h
#define monitor_h

//numero de filosofos, pode ser alterado
//
#define NUMERO_FILOSOFOS 5

//estados

#define PENSANDO 0
#define FOME 1
#define COMENDO 2

//definindo a estrutura do circulo

#define ESQUERDA (i+NUMERO_FILOSOFOS-1)%NUMERO_FILOSOFOS
#define DIREITA (i+1)%NUMERO_FILOSOFOS

//funcoes que utilizarei
void iniciar();
void testar( int i);
void pegar_talher(int i);
void soltar_talher(int i);

#endif

