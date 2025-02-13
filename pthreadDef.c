//Author: Connor Hanson, Tiger Ji

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "queue.h"
#include <ctype.h>
#include "pthreadDef.h"

#define BUFF_SIZE 100

/**
 * Reader thread function
 *
 * @param:
 *	void *arg - pointer to queue 1
 */
void *reader(void *arg){
	char *input;
	char nextChar = getc(stdin);
	while(nextChar != EOF){ // read until EOF
		if(nextChar != '\n'){
			if((input = malloc(BUFF_SIZE))){ // allocate string space, make sure space allocates properly
				input[0] = nextChar; // build string
				int counter = 1; // line length
				while(nextChar != EOF && nextChar != '\n'){ // read until end of line/EOF
					counter++;
					nextChar = getc(stdin);
					if((counter-1) < BUFF_SIZE && nextChar != '\n'){
						input[counter-1] = nextChar;
					}
				}
				input[counter] = '\0';
				if((counter - 1) > BUFF_SIZE){ // flush line if longer than allowed size
					fprintf(stderr, "\nError: cutting off excess input\n");
				} else {
					enqueueString((Queue *)arg, input);
				}
				//enqueueString((Queue *)arg, input);
			}
			else{
				exit(EXIT_FAILURE);
				//return NULL;
			}
		}
		nextChar = getc(stdin);
	}
	enqueueString((Queue *)arg, NULL); // enqueue NULL at EOF
	return NULL;
}

/**
 * Munch1 thread function
 *
 * @param:
 *	void *arg - Queue ** containing queue 1 and queue 2
 		[0] - queue 1 pointer
 		[1] - queue 2 pointer
 */
void *munch1(void *arg){
	char *input = "";
	while(input != NULL){ // keep processing until EOF
		input = dequeueString(((Queue **)arg)[0]);
		if(input != NULL){
			int i;
			for(i = 0; i < BUFF_SIZE; i++){
				if(input[i] == ' '){ // replace spaces with *
					input[i] = '*';
				}
			}
		}
		enqueueString(((Queue **)arg)[1], input);
	}
	return NULL;
}

/**
 * Munch1 thread function
 *
 * @param:
 *	void *arg - Queue ** containing queue 2 and queue 3
 		[0] - queue 2 pointer
 		[1] - queue 3 pointer
 */
void *munch2(void *arg){
	char *input = "";
	while(input != NULL){ // keep processing until EOF
		input = dequeueString(((Queue **)arg)[0]);
		if(input != NULL){
			int i;
			for(i = 0; i < BUFF_SIZE; i++){ // lower to upper case
				if(islower(input[i])){
					char c = input[i];
					input[i] = toupper(c);
				}
			}
		}
		enqueueString(((Queue **)arg)[1], input);
	}
	return NULL;
}

/**
 * Writer thread function
 *
 * @param:
 *	void *arg - pointer to queue 3
 */
void *writer(void *arg){
	char *input = "";
	int processed = 0; // track processed lines
	while(input != NULL){ // keep processing until EOF
		input = dequeueString((Queue *)arg);
		if(input != NULL){
			printf("%s\n", input);
			free(input);
			processed++;
		}
	}
	printf("Lines processed: %d\n", processed);
	return NULL;
}
