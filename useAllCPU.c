#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *threadFunction(void *var)
{
	int thread_id = *(int *)var;

	// TODO Write code to make me run for at least a minute
	time_t end = time(NULL) + 60;
	while (time(NULL) <= end) {
		sqrt(279);
	}
}

int main(int argc, char **argv)
{
	int P = 4;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for (i = 0; i < P; i++)
		thread_id[i] = i;

	for (i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
