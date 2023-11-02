#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define SUBSTR_FOUND 1
#define PARTIAL_SUBSTR_FOUND 2
#define SUBSTR_NOT_FOUND 0

pthread_mutex_t shortestRemainder_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct thread_data {
	int thread_id;
	char remainder_substr[20];
	int result;
} thread_data;

char* buffer;
int file_size;
char* substring;
int threads;
char shortestRemainder[20];

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

bool findSubstring(const char* buf, const char* substr)
{
	if (strstr(buf, substr)) {
		return true;

	} else {
		return false;
	}
}

char* findPartialSubstring(char* buf, char* substr)
{
	int bufLen = strlen(buf);
	int substrLen = strlen(substr);
	int maxLen = 0;

	for (int i = 0; i < bufLen; i++) {
		int j = 0;
		while (i + j < bufLen && j < substrLen && buf[i + j] == substr[j]) {
			j++;
		}

		if (j > maxLen) {
			maxLen = j;
		}
	}

	if (maxLen < substrLen) {
		char* remaining = malloc(substrLen - maxLen + 1);
		int index = 0;
		for (int i = maxLen; i < substrLen; i++) {
			remaining[index++] = substr[i];
		}
		remaining[index] = '\0';

		return remaining;
	} else {
		return NULL;
	}
}

void writeToShortestRemainder(char* str)
{
	pthread_mutex_lock(&shortestRemainder_mutex);
	if (strlen(str) < strlen(shortestRemainder)) {
		memset(shortestRemainder, 0, 20);
		printf("%s\n", str);
		strcpy(shortestRemainder, str);
	} else {
		pthread_mutex_unlock(&shortestRemainder_mutex);
	}

	pthread_mutex_unlock(&shortestRemainder_mutex);
}

char* reverseString(const char* str)
{
	int str_len = strlen(str);
	char* revved_str = malloc((str_len + 1) * sizeof(char));

	for (int i = 0; i < str_len; i++) {
		revved_str[str_len - 1 - i] = str[i];
	}
	revved_str[str_len] = '\0';

	// printf("Reversed: %s\n", revved_str);
	return revved_str;
}
char* checkStartOfBuffer(char* buf, char* substr)
{
	int buf_len = strlen(buf);
	int substr_len = strlen(substr);
	char* rev_substr = reverseString(substr);

	for (int i = 0; i < substr_len; i++) {
		strncmp(buf, )
	}
}

void* threadRoutine(void* var)
{
	thread_data* tdata = (thread_data*)var;
	int thread_id = tdata->thread_id;

	double ownElems = (double)strlen(buffer) / threads;
	int start = thread_id * (double)ceil(ownElems);
	int end = min(strlen(buffer), ((thread_id + 1) * (double)ceil(ownElems)));

	int own_buffer_len = end - start;
	char* own_buffer = malloc((own_buffer_len + 1) * sizeof(char));
	own_buffer[own_buffer_len] = '\0';
	int j = 0;
	for (int i = start; i < end; i++) {
		own_buffer[j] = buffer[i];
		j++;
	}

	printf("Thread %d has to search among this part of text: %s\n", thread_id, own_buffer);

	if (findSubstring(own_buffer, substring)) {
		// printf("Thread %d has found the substring %s\n", thread_id, substring);
		tdata->result = SUBSTR_FOUND;
		pthread_exit(NULL);
	} else {
		char* remaining = findPartialSubstring(own_buffer, substring);
		if (remaining != NULL) {
			if (strcmp(remaining, substring) != 0) {
				// printf("remaining substring to be found: %s\n", remaining);
				strcpy(tdata->remainder_substr, remaining);
				tdata->result = PARTIAL_SUBSTR_FOUND;
				writeToShortestRemainder(remaining);
			} else {
				tdata->result = SUBSTR_NOT_FOUND;
			}
		}
		pthread_exit(NULL);
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
		memset(tdata[i].remainder_substr, 0, 20);
		tdata[i].result = 0;
	}
	for (int i = 0; i < threads; i++) {
		pthread_create(&tid[i], NULL, threadRoutine, &tdata[i]);
	}
	for (int i = 0; i < threads; i++) {
		pthread_join(tid[i], NULL);
	}

	int check = 0;
	for (int i = 0; i < threads; i++) {
		if (tdata[i].result == SUBSTR_FOUND) {
			printf("Thread %d found the substring\n", tdata[i].thread_id);
			check = 1;
			break;
		}
	}

	if (check == 0) {
		for (int i = 0; i < threads; i++) {
			if (tdata[i].result == PARTIAL_SUBSTR_FOUND) {
				printf("Thread %d found part of the substring and the remaining substring is: %s\n", tdata[i].thread_id, tdata[i].remainder_substr);
				check = 1;
			}
		}
	}

	printf("Shortest remainder: %s\n", shortestRemainder);

	reverseString("nice");

	return 0;
}