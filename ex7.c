#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *threadRoutine(void *var)
{
	int thread_id = *(int *)var;
	printf("Hello world from thread %i\n", thread_id);
}

void *threadRoutine2(void *var)
{
	int thread_id = *(int *)var;
	printf("Salutare Planeta from thread %i\n", thread_id);
}

int main()
{
	int threads = 2;

	pthread_t tid[threads];
	int thread_id[threads];

	for (int i = 0; i < threads; i++) {
		thread_id[i] = i;
	}

	pthread_create(&tid[0], NULL, threadRoutine, &thread_id[0]);
	pthread_create(&tid[1], NULL, threadRoutine2, &thread_id[1]);

	for (int i = 0; i < threads; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}