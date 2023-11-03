#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *threadRoutine(void *var)
{
	int thread_id = *(int *)var;
	for (int i = 0; i < 10000; i++) {
		// pthread_mutex_lock(&mutex);
		printf("iter: %d --- Hello world from thread %i\n", i, thread_id);
		// pthread_mutex_unlock(&mutex);
		// fflush(stdout);
		// sched_yield();
		// usleep(1000);
	}
}

int main()
{
	long cpus = sysconf(_SC_NPROCESSORS_ONLN);
	int threads = (int)cpus;

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