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

bool findSubstring(const char* buf, const char* substr)
{
	if (strstr(buf, substr)) {
		return true;

	} else {
		return false;
	}
}

char* rotateString(const char* str)
{
	int length = strlen(str);
	char* rotatedStr = (char*)malloc((length + 1) * sizeof(char));

	strcpy(rotatedStr, str);

	if (length <= 1) {
		return rotatedStr;
	}

	char temp = rotatedStr[length - 1];
	memmove(rotatedStr + 1, rotatedStr, length - 1);
	rotatedStr[0] = temp;

	// printf("%s\n", rotatedStr);
	return rotatedStr;
}

char* checkLeft(char* buf, char* substr)
{
	int buf_len = strlen(buf);
	int substr_len = strlen(substr);
	char* tmp = malloc(substr_len * sizeof(char));

	strcpy(tmp, substr);

	tmp = rotateString(substr);
	int index = 0;
	for (int i = 1; i <= substr_len; i++) {
		// printf("left -> buf: %s | tmp: %s | i: %d\n", buf, tmp, i);
		if (strncmp(buf, tmp, i) == 0) {
			index = i;
			break;
		} else {
			// printf("checkLeft: %s\n", tmp);
			tmp = rotateString(tmp);
		}
	}

	if (index == 0) {
		free(tmp);
		return NULL;
	} else {
		char* result = malloc((index + 1) * sizeof(char));
		strncpy(result, tmp, index);
		result[index] = '\0';
		// printf("LEFT: Part of substring found: %s\n", result);
		free(tmp);
		return result;
	}
	return NULL;
}

char* checkRight(char* buf, char* substr)
{
	int buf_len = strlen(buf);
	int substr_len = strlen(substr);
	char* tmp = malloc(buf_len * sizeof(char));

	strcpy(tmp, buf);

	tmp = rotateString(buf);
	int index = 0;
	for (int i = 1; i <= buf_len; i++) {
		// printf("right -> substr: %s | tmp: %s | i: %d\n", substr, tmp, i);
		if (strncmp(substr, tmp, i) == 0) {
			index = i;
			break;
		} else {
			// printf("checkLeft: %s\n", tmp);
			tmp = rotateString(tmp);
		}
	}

	if (index == 0) {
		free(tmp);
		return NULL;
	} else {
		char* result = malloc((index + 1) * sizeof(char));
		strncpy(result, tmp, index);
		result[index] = '\0';
		// printf("RIGHT: Part of substring found: %s\n", result);
		free(tmp);
		return result;
	}
	return NULL;
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
		tdata->result = SUBSTR_FOUND;
		pthread_exit(NULL);
	} else {
		tdata->second_part = checkLeft(own_buffer, substring);
		tdata->first_part = checkRight(own_buffer, substring);
		// printf("thread %d -> -first: %s | -second: %s\n", thread_id, tdata->first_part, tdata->second_part);
		if (tdata->first_part != NULL && tdata->second_part == NULL) {
			tdata->result = LEFTPART_SUBSTR_FOUND;
		}
		if (tdata->first_part == NULL && tdata->second_part != NULL) {
			tdata->result = RIGHTPART_SUBSTR_FOUND;
		}
		if (tdata->first_part == NULL && tdata->second_part == NULL) {
			tdata->result = SUBSTR_NOT_FOUND;
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
		// memset(tdata[i].remainder_substr, 0, 20);
		tdata[i].result = 0;
	}
	for (int i = 0; i < threads; i++) {
		pthread_create(&tid[i], NULL, threadRoutine, &tdata[i]);
	}
	for (int i = 0; i < threads; i++) {
		pthread_join(tid[i], NULL);
	}

	for (int i = 0; i < threads; i++) {
		if (tdata[i].result == SUBSTR_FOUND) {
			printf("Thread %d found the substring %s\n", tdata[i].thread_id, substring);
			break;
		} else if (tdata[i].result == LEFTPART_SUBSTR_FOUND) {
			printf("Thread %d found the first part of the substring: %s\n", tdata[i].thread_id, tdata[i].first_part);
		} else if (tdata[i].result == RIGHTPART_SUBSTR_FOUND) {
			printf("Thread %d found the second part of the substring: %s\n", tdata[i].thread_id, tdata[i].second_part);
		} else {
			printf("Thread %d has not found anything\n", tdata[i].thread_id);
		}
	}

	char result[20];
	for (int i = 0; i < threads; i++) {
		if (tdata[i].result == LEFTPART_SUBSTR_FOUND) {
			strcpy(result, tdata[i].first_part);
		}
		for (int j = 0; j < threads; j++) {
			if (tdata[j].result == RIGHTPART_SUBSTR_FOUND) {
				strcat(result, tdata[j].second_part);
				if (strcmp(result, substring) == 0) {
					printf("result %s\n", result);
					printf("done\n");
					printf("Substring is part found in thread %d (%s) and part found in thread %d (%s)\n", i, tdata[i].first_part, j, tdata[j].second_part);
					break;
				}
			}
		}
	}
	return 0;
}