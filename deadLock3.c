#define _XOPEN_SOURCE 600
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int printLevel;
int N;
int P;

pthread_mutex_t mutex;
sem_t sem;

void *
threadFunction(void *var)
{
	// TODO preserve the correct order by using barriers
	int thread_id = *(int *)var;
	if (thread_id == 0) {
		sem_wait(&sem);
		pthread_mutex_lock(&mutex);
		// pthread_mutex_lock(&mutex);
		printf("There should be two messages displayed, I am one of them\n");
	} else {
		printf("There should be two messages displayed, I am one of them\n");
		sem_post(&sem);
	}
}

int main(int argc, char *argv[])
{
	P = 2;  // ATTENTION, WE OVERWRITE THE NUMBER OF THREADS. WE ONLY NEED 2
	int i;

	pthread_mutex_init(&mutex, NULL);
	pthread_t tid[P];
	int thread_id[P];
	for (i = 0; i < P; i++)
		thread_id[i] = i;

	sem_init(&sem, 0, 0);
	// DO NOT EDIT
	for (i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	// DO NOT EDIT
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	// DO NOT EDIT
	pthread_mutex_destroy(&mutex);
	return 0;
}
