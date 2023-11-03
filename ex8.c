#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *threadRoutine(void *var)
{
}

int main()
{
	int err = 0;
	int count = 0;
	pthread_t tid;

	while (err == 0) {
		err = pthread_create(&tid, NULL, threadRoutine, NULL);
		count++;
	}
	printf("Max number of threads within a process is: %d\n", count);

	return 0;
}