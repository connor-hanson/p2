ARGS = -c -Wall -Wextra -pthread -g

all: 
	gcc $(ARGS) queue.c
	gcc $(ARGS) main.c
	gcc $(ARGS) pthreadDef.c
	gcc $(ARGS) queueStat.c
	gcc -o prodcom -Wall -Wextra -pedantic -pthread -g queue.o main.o pthreadDef.o queueStat.o

clean: 
	rm -f queue.o pthreadDef.o queueStat.o testQueue.o main.o prodcom out

test: 
	gcc $(ARGS) queue.c
	#gcc $(ARGS) main.c
	gcc $(ARGS) pthreadDef.c
	gcc $(ARGS) queueStat.c
	gcc $(ARGS) tests/testQueue.c
	gcc -o test -Wall -Wextra -pedantic -pthread -g queue.o pthreadDef.o queueStat.o testQueue.o
