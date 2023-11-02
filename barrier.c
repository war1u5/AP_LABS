#define _XOPEN_SOURCE 600
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_barrier_t barrier;
pthread_barrier_t barrier_1st;

int printLevel;
int N;
int P;

void *threadFunction(void *var)
{
	// TODO preserve the correct order by using barriers
	int thread_id = *(int *)var;

	if (thread_id == 0) {
		pthread_barrier_wait(&barrier);
		pthread_barrier_wait(&barrier);
		printf("I should be displayed last\n");
	}

	else if (thread_id == 1) {
		pthread_barrier_wait(&barrier);
		printf("I should be displayed in the middle\n");
		pthread_barrier_wait(&barrier);
	}

	else if (thread_id == 2) {
		printf("I should be displayed first\n");
		pthread_barrier_wait(&barrier);
		pthread_barrier_wait(&barrier);
	}
}

int main(int argc, char *argv[])
{
	// getArgs(argc, argv);
	// init();

	P = 3;  // ATTENTION, WE OVERWRITE THE NUMBER OF THREADS. WE ONLY NEED 3
	int i;

	pthread_t tid[P];
	int thread_id[P];

	pthread_barrier_init(&barrier, NULL, P);

	for (i = 0; i < P; i++)
		thread_id[i] = i;
	// DO NOT EDIT
	for (i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	// DO NOT EDIT
	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	// DO NOT EDIT
	// print();

	pthread_barrier_destroy(&barrier);

	return 0;
}
