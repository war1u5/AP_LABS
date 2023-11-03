SOURCES := helloWorld.c ex2.c ex3.c ex5.c ex6.c ex7.c ex8.c
EXECUTABLES := $(SOURCES:.c=.exe)
CC := gcc
CFLAGS := -lm -O3 -lpthread

all: $(EXECUTABLES)
$(EXECUTABLES): %.exe : %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLES)
