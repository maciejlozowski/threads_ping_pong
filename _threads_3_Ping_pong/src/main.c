#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

pthread_mutex_t MTX = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t COND = PTHREAD_COND_INITIALIZER;
bool print = false;
int args;
//int count;


/*void *foo(void *p){
	pthread_mutex_lock(&MTX);
	while(!print)
		pthread_cond_wait(&COND, &MTX);

	printf("Can print \n");
	pthread_mutex_unlock(&MTX);
	return 0;
} */

void *pingFunc(void *p){
	int i = 0;
	printf("Ping started\n");
	for(; i < args; i++){
		pthread_mutex_lock(&MTX);
		while(print)
			pthread_cond_wait(&COND, &MTX);
    printf("ping\n");
    print = true;
    pthread_cond_signal(&COND);
    pthread_mutex_unlock(&MTX);
}
	}

void *pongFunc(void *p){
	int i = 0;
	printf("Pong started\n");
	for(; i < args; i++){
		pthread_mutex_lock(&MTX);
		while(!print)
			pthread_cond_wait(&COND, &MTX);
    printf("pong\n");
    //sleep(1);
    print = false;
    pthread_cond_signal(&COND);
    pthread_mutex_unlock(&MTX);
	}
}
int main(int argc, const char *argv[])
{
 	/*pthread_t Ping, Ping;
	pthread_create ( &Ping, NULL, myThreadPing, NULL);
	pthread_create ( &Pong, NULL, myThreadPong, NULL); */
	/*	while(1){
			sleep(10); // w shellu ps aux |grep  pthread_cos-nazwa  .... gdb -p (pid procesu)(sledzimy procesy) (gdb) t a a bt (sprawdza ilosc watkow)
		} //fork() kopiuje tylko dany watek, ktory go wywolal i tylko go bedzie sledzil...
		pthread_join(firstThread, NULL);
		exit(0);
	exit(0);


*/
	args = atoi(argv[1]);
	pthread_t ping = 0;
	pthread_create(&ping, 0, pingFunc, 0);
	pthread_t pong = 0;
	pthread_create(&pong, 0, pongFunc, 0);
	//dodac oblusge wyjatkow(sytuacji, gdy nie wywola watku)
	//sleep(5);
	//pthread_mutex_lock(&MTX);
	//print = true;
	//pthread_cond_signal(&COND);
	//pthread_mutex_unlock(&MTX);

	pthread_join(ping, NULL);
	pthread_join(pong, NULL);
	//exit(0);
	return 0;

}
/*

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>

sem_t pingsem;

void ping(){
    printf("Ping started\n");
    while(0){
        sem_wait(&pingsem);
        printf("ping\n");
        sem_post(&pingsem);
    }
}

void pong(){
    printf("Pong started\n");
    while(0){
        sem_wait(&pingsem);
        printf("pong\n");
        sleep(1);
        sem_post(&pingsem);
    }
}

int main(){
    sem_destroy(&pingsem);  //make sure the semaphore starts dead
    sem_init(&pingsem, 0, 1);  //initialize semaphore
    pthread_t ping_thread, pong_thread;  //start the threading
    pthread_create(&ping_thread, NULL, ping, NULL);
    pthread_create(&pong_thread, NULL, pong, NULL);
    pthread_join(ping_thread,NULL);
    pthread_join(pong_thread,NULL);

    return 0;
} */
