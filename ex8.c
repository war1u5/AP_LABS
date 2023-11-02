#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* buffer;
int file_size;
char* substring;

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
	if (strstr(buffer, substring)) {
		return true;

	} else {
		return false;
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

	if (findSubstring()) {
		printf("The substring %s exists within the string\n", argv[2]);
	} else {
		printf("Not found\n");
	}

	return 0;
}