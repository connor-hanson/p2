ARGS = -c -Wall -Wextra -pthread -g

all: 
	gcc $(ARGS) queue.c
	gcc $(ARGS) main.c
	gcc $(ARGS) pthreadDef.c
	gcc $(ARGS) queueStat.c
	gcc -o prodcom -Wall -Wextra -pedantic -pthread -g queue.o main.o pthreadDef.o queueStat.o

clean: 
	rm -f queue.o testQueue.o test out

test: 
	gcc $(ARGS) -g queue.c
	gcc $(ARGS) -g tests/testQueue.c
	gcc -o test queue.o testQueue.o
