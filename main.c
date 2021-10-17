#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "monitor.h"

void *jantar(void *i){
	while(1){
		//declarar filosofo
		int atual=*(int *)i;
		int n,m;
		n=rand();
		n=n%10;
		printf("\n Filosofo %d esta pensando por %d s",atual,n);
		//segurar os n seg
		sleep(n);
		pegar_talher(atual);
		
		m= rand();
		m= m % 7;
		printf("\n Filosofo %d esta comendo por %d s",atual,m);
		sleep(m);
		soltar_talher(atual);
	}

}


int main()
{
	int i, pos[NUMERO_FILOSOFOS];
	pthread_t thread[NUMERO_FILOSOFOS];
	pthread_attr_t attr;

	iniciar();

	pthread_attr_init(&attr);

	for (i = 0; i < NUMERO_FILOSOFOS; i++) 
	{
		pos[i] = i;
		//create thread corresponding to each philosopher
		pthread_create(&thread[i], NULL,jantar, (int *) &pos[i]);
	}
	for (i = 0; i < NUMERO_FILOSOFOS; i++)
	{
		pthread_join(thread[i], NULL);
	}

	return 0;
}



