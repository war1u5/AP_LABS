#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int** matrix1;
int** matrix2;
int** matrix3;
int rows;
int cols;
int threads;

void initMatrix(int*** matrix, int rows, int cols)
{
	*matrix = (int**)malloc(rows * sizeof(int*));
	for (int i = 0; i < rows; i++) {
		(*matrix)[i] = (int*)malloc(cols * sizeof(int));
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			(*matrix)[i][j] = rand() % 100;
		}
	}
}

void printMatrix(int** matrix)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void addMatrix(int** mat1, int** mat2, int start, int end)
{
	for (int i = start; i < end; i++) {
		for (int j = 0; j < cols; j++) {
			matrix3[i][j] = 0;
			matrix3[i][j] = mat1[i][j] + mat2[i][j];
			// printf("%d ", matrix3[i][j]);
		}
		// printf("\n");
	}
}

void* threadRoutine(void* var)
{
	int thread_id = *(int*)var;
	printf("hello from thread %d\n", thread_id);

	double ownElems = (double)rows / (double)threads;
	int start = thread_id * (double)ceil(ownElems);
	int end = min(rows, (thread_id + 1) * (double)ceil(ownElems));

	printf("Thread %d has this matrix: \n", thread_id);

	for (int i = start; i < end; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", matrix1[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	for (int i = start; i < end; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d ", matrix2[i][j]);
		}
		printf("\n");
	}

	addMatrix(matrix1, matrix2, start, end);
}

int main(int argc, char* argv[])
{
	if (argc < 1) {
		printf("not enough args\n");
		exit(-1);
	}
	rows = atoi(argv[1]);
	cols = atoi(argv[2]);
	threads = atoi(argv[3]);

	srand(time(NULL));
	initMatrix(&matrix1, rows, cols);
	initMatrix(&matrix2, rows, cols);
	initMatrix(&matrix3, rows, cols);

	// printMatrix(matrix1);
	printf("\n");
	// printMatrix(matrix2);

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

	printf("Result:\n");
	// addMatrix(matrix1, matrix2);
	printMatrix(matrix3);

	return 0;
}