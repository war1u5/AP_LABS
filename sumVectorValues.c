#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct thread_data {
	int thread_id;
	long long int mysum;
} thread_data;

int printLevel;
int N;
int P;
long long *v;
long long sum;

void getArgs(int argc, char **argv)
{
	if (argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

long long *allocVector(int N)
{
	long long *v = malloc(sizeof(long long) * N);
	if (v == NULL) {
		printf("malloc failed!");
		exit(1);
	}
	return v;
}

void init()
{
	v = allocVector(N);

	long long i;
	for (i = 0; i < N; i++) {
		v[i] = i + 1;
	}
}

void printPartial()
{
	printf("Sum: %lli \n", sum);
}

void printAll()
{
	printPartial();
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

void *threadRoutine(void *var)
{
	thread_data *tdata = (thread_data *)var;
	int thread_id = tdata->thread_id;

	double ownElems = (double)N / (double)P;
	int start = thread_id * (double)ceil(ownElems);
	int end = min(N, ((thread_id + 1) * (double)ceil(ownElems)));

	// printf("Thread %d elems are: \n", thread_id);
	for (int i = start; i < end; i++) {
		// printf("%lld, ", v[i]);
		tdata->mysum = tdata->mysum + v[i];
	}
	printf("\n");

	// printf("Thread %d sum is %lld\n", thread_id, tdata->mysum);
}

int main(int argc, char *argv[])
{
	getArgs(argc, argv);
	init();

	long long i;
	int threads = P;
	pthread_t tid[threads];
	int thread_id[threads];
	thread_data tdata[threads];

	for (int i = 0; i < threads; i++) {
		tdata[i].thread_id = i;
		tdata[i].mysum = 0;
	}

	for (int i = 0; i < threads; i++) {
		pthread_create(&tid[i], NULL, threadRoutine, &tdata[i]);
	}

	for (int i = 0; i < threads; i++) {
		pthread_join(tid[i], NULL);
	}

	// long long int totalSum = 0;
	for (int i = 0; i < threads; i++) {
		sum = sum + tdata[i].mysum;
	}
	// for (i = 0; i < N; i++)
	// 	sum += v[i];

	print();

	return 0;
}
