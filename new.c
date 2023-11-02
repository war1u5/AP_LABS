#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define SUBSTR_FOUND 1
#define LEFTPART_SUBSTR_FOUND 2
#define RIGHTPART_SUBSTR_FOUND 3
#define SUBSTR_NOT_FOUND 0

typedef struct thread_data {
	int thread_id;
	char* second_part;
	char* first_part;
	int result;
} thread_data;

char* buffer;
int file_size;
char* substring;
int threads;

void initBuffer(int bufsize)
{
	buffer = malloc((bufsize + 1) * sizeof(char));
}

void readFile(const char* filename)
{
	FILE* f = fopen(filename, "r");

	fseek(f, 0, SEEK_END);
	file_size = ftell(f);
	fseek(f, 0, SEEK_SET);

	initBuffer(file_size);

	fread(buffer, 1, file_size, f);

	fclose(f);
}

void initSubstring(int len, char* string)
{
	substring = malloc(len * sizeof(char));
	strcpy(substring, string);
}

bool findSubstring()
{
	int sub_len = strlen(substring);
	int buf_len = strlen(buffer);
	for (int i = 0; i <= buf_len - sub_len; i++) {
		int j;
		for (j = 0; j < sub_len; j++) {
			if (buffer[i + j] != substring[j]) {
				break;
			}
		}
		if (j == sub_len) {
			return true;
		}
	}
	return false;
}

void* threadRoutine(void* var)
{
	thread_data* tdata = (thread_data*)var;
	int thread_id = tdata->thread_id;

	double ownElems = (double)strlen(buffer) / threads;
	int start = thread_id * (double)ceil(ownElems);
	int end = min(strlen(buffer), ((thread_id + 1) * (double)ceil(ownElems)));

	printf("Thread %d has to search among this part of text:\n", thread_id);
	for (int i = start; i < end; i++) {
		printf("%c", buffer[i]);
	}
	printf("\n");

	int j = 0;
	int count = 1;
	int ownBufSize = end - start;
	int str_len = strlen(substring);

	for (int i = start; i < end; i++) {
		count = 1;
		if (buffer[i] == substring[0]) {
			j++;
			printf("%c\n", buffer[i]);
			while (buffer[i + j] == substring[j]) {
				j++;
				count++;
				if ((i + j) == ownBufSize) {
					printf("am gasit ceva dar am ajuns la limita\n");
					printf("count %d\n", count);
					printf("Trebuie sa caut restul de %d caractere in continuare\n", str_len - count);
					for (int k = end; k < end + 3; k++) {
						printf("%c", buffer[k]);
					}
					printf("\n");
					break;
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3) {
		printf("not enough args\n");
		exit(-1);
	}

	readFile(argv[1]);

	int substring_len = strlen(argv[2]);
	initSubstring(substring_len, argv[2]);

	threads = atoi(argv[3]);
	pthread_t tid[threads];
	int thread_id[threads];
	thread_data tdata[threads];

	for (int i = 0; i < threads; i++) {
		tdata[i].thread_id = i;
		// memset(tdata[i].remainder_substr, 0, 20);
		tdata[i].result = 0;
	}
	for (int i = 0; i < threads; i++) {
		pthread_create(&tid[i], NULL, threadRoutine, &tdata[i]);
	}
	for (int i = 0; i < threads; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}