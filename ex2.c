#include <stdio.h>
#include <unistd.h>

int main()
{
	long cpus = sysconf(_SC_NPROCESSORS_ONLN);

	if (cpus != -1) {
		printf("Number of CPUs: %ld\n", cpus);
	} else {
		perror("Error");
	}

	return 0;
}