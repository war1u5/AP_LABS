SOURCES := addVectors-par.c addVectors-seq.c ex6.c ex7.c ex8.c ex9.c helloWorld.c new.c useAllCPU.c
EXECUTABLES := $(SOURCES:.c=)
CC := gcc
CFLAGS := -lm -lpthread

all: $(EXECUTABLES)
$(EXECUTABLES): % : %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(EXECUTABLES)
