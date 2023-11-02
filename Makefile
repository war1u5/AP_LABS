SOURCES := raceCondition.c raceCondition-seq.c barrier.c barrier-seq.c semaphoreSignal.c semaphoreSignal-seq.c deadLock1.c deadLock2.c deadLock3.c sumVectorValues.c prepStrassen.c
EXECUTABLES := $(SOURCES:.c=.exe)
CC := gcc
CFLAGS := -lm -lpthread

all: $(EXECUTABLES)
$(EXECUTABLES): %.exe : %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(EXECUTABLES)
