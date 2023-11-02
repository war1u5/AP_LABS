#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int NReps;
int printLevel;
int N;
int P;
int* a;
int* b;
int* c;

void getArgs(int argc, char** argv)
{
	if (argc < 5) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
	NReps = atoi(argv[4]);
}

void init()
{
	a = malloc(sizeof(int) * N);
	b = malloc(sizeof(int) * N);
	c = malloc(sizeof(int) * N);
	if (a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i;
	for (i = 0; i < N; i++) {
		a[i] = i % 500;
		b[i] = i % 500;
	}
}

void printPartial()
{
	int i;
	for (i = 0; i < 10; i++)
		printf("%i ", c[i]);
	printf("\n");
	for (i = 20; i < N; i += N / 10)
		printf("%i ", c[i]);
	printf("\n");
	for (i = N - 10; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

void printAll()
{
	int i;
	for (i = 0; i < N; i++)
		printf("%d ", c[i]);
	printf("\n");
}

void print()
{
	if (printLevel == 0)
		return;
	else if (printLevel == 1)
		printPartial();
	else
		printAll();
}

void* threadRoutine(void* var)
{
	// NReps = 2;
	int thread_id = *(int*)var;

	// printf("Hello from thread: %d\n", thread_id);

	double ownElems = (double)N / (double)P;
	int start = thread_id * (double)ceil(ownElems);
	int end = min(N, ((thread_id + 1) * (double)ceil(ownElems)));

	// printf("The vectors of thread %d are:\n", thread_id);
	// for (int i = start; i < end; i++) {
	// 	printf("%d ", a[i]);
	// }
	// printf("\n");
	// for (int i = start; i < end; i++) {
	// 	printf("%d ", b[i]);
	// }

	// printf("\n");
	for (int j = 0; j < NReps; j++)
		for (int i = start; i < end; i++) {
			c[i] = a[i] + b[i];
			// printf("%d = %d + %d\n", c[i], a[i], b[i]);
		}

	// printf("Thread %d has calculated the following vector: \n", thread_id);
	// for (int i = start; i < end; i++) {
	// 	printf("%d ", c[i]);
	// }
	// printf("\n");

	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	getArgs(argc, argv);
	init();

	int threads = P;
	pthread_t tid[threads];
	int thread_id[threads];

	// TODO paralelize me
	for (int i = 0; i < threads; i++) {
		thread_id[i] = i;
	}
	for (int i = 0; i < threads; i++) {
		pthread_create(&tid[i], NULL, threadRoutine, &thread_id[i]);
	}
	for (int i = 0; i < threads; i++) {
		pthread_join(tid[i], NULL);
	}

	// printf("Result: \n");
	print();

	free(a);
	free(b);
	free(c);

	return 0;
}
