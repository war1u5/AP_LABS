#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int printLevel;
int N;
int P;
int A11, A12, A21, A22, B11, B12, B21, B22;
int M1, M2, M3, M4, M5, M6, M7;
int C11, C12, C21, C22;

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

void init()
{
	A11 = 3213215;
	A12 = 5454;
	A21 = 5456;
	A22 = 9898;
	B11 = 54544;
	B12 = 90821;
	B21 = 9807879;
	B22 = 329132;
}

void printPartial()
{
	printf("%i %i %i %i \n", C11, C12, C21, C22);
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
	int thread_id = *(int *)var;

	if (thread_id == 0) {
		M1 = (A11 + A22) * (B11 + B22);
	} else if (thread_id == 1) {
		M2 = (A21 + A22) * B11;
	} else if (thread_id == 2) {
		M3 = A11 * (B12 - B22);
	} else if (thread_id == 3) {
		M4 = A22 * (B21 - B11);
	} else if (thread_id == 4) {
		M5 = (A11 + A12) * B22;
	} else if (thread_id == 5) {
		M6 = (A21 - A11) * (B11 + B12);
	} else if (thread_id == 6) {
		M7 = (A12 - A22) * (B21 + B22);
	} else {
		printf("N-ar trebui sa exist :))))) %d\n", thread_id);
	}
}

int main(int argc, char *argv[])
{
	getArgs(argc, argv);
	init();

	long long i;
	int threads = 7;
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

	C11 = M1 + M4 - M5 + M7;
	C12 = M3 + M5;
	C21 = M2 + M4;
	C22 = M1 - M2 + M3 + M6;

	print();

	return 0;
}
