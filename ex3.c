#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *threadRoutine(void *var)
{
	int thread_id = *(int *)var;

	printf("Hello world from thread %i\n", thread_id);

	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("not enough args\n");
		exit(-1);
	}
	int threads = atoi(argv[1]);
	pthread_t tid[threads];
	int thread_id[threads];

	for (int i = 0; i < threads; i++) {
		thread_id[i] = i;
	}

	for (int i = 0; i < threads; i++) {
		pthread_create(&tid[i], NULL, threadRoutine, &thread_id[i]);
	}

	for (int i = 0; i < threads; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}