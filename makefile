CC = gcc
WARNING_FLAGS = -Wall -Wextra
OPTS = -pthread -g
EXE = prodcom
SCAN_BUILD_DIR = scan-build-out

all: main.o pthreadDef.o queueStat.o queue.o
	$(CC) $(OPTS) -o $(EXE) main.o pthreadDef.o queueStat.o queue.o

main.o: main.c queue.h pthreadDef.h queueStat.h
	$(CC) $(OPTS) $(WARNING_FLAGS) -c main.c

pthreadDef.o: pthreadDef.c queue.h
	$(CC) $(OPTS) $(WARNING_FLAGS) -c pthreadDef.c

queueStat.o: queueStat.c queue.h
	$(CC) $(OPTS) $(WARNING_FLAGS) -c queueStat.c
	
queue.o: queue.c queueStat.h
	$(CC) $(OPTS) $(WARNING_FLAGS) -c queue.c

clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make
