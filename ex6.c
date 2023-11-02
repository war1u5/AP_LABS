#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** matrix1;
int** matrix2;
int** matrix3;
int rows;
int cols;

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

void addMatrix(int** mat1, int** mat2)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix3[i][j] = 0;
			matrix3[i][j] = mat1[i][j] + mat2[i][j];
			// printf("%d ", matrix3[i][j]);
		}
		// printf("\n");
	}
}

int main(int argc, char* argv[])
{
	if (argc < 1) {
		printf("not enough args\n");
		exit(-1);
	}
	rows = atoi(argv[1]);
	cols = atoi(argv[2]);

	srand(time(NULL));
	initMatrix(&matrix1, rows, cols);
	initMatrix(&matrix2, rows, cols);
	initMatrix(&matrix3, rows, cols);

	printMatrix(matrix1);
	printf("\n");
	printMatrix(matrix2);

	printf("\n");
	addMatrix(matrix1, matrix2);
	printMatrix(matrix3);

	return 0;
}