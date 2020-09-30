ARGS = -c -Wall -Wextra

all: 
	gcc $(ARGS) queue.c
	gcc -o out -Wall -Wextra queue.o

clean: 
	rm -f queue.o testQueue.o test out

test: 
	gcc $(ARGS) queue.c
	gcc $(ARGS) tests/testQueue.c
	gcc -o test queue.o testQueue.o