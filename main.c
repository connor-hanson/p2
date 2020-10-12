//Author: Connor Hanson, Tiger Ji

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "queue.h"

#define BUFF_SIZE 100
#define QUEUE_SIZE 10

pthread_t read, mun1, mun2, writ;

sem_t resource;
sem_t writer;
sem_t reader;

static Queue *q1;
static Queue *q2;
static Queue *q3;

// Read from stdio, one line at a time. 
// Pass each line of the input to Munch1 through a queue of character strings
void *reader(void *arg){
	char *input;
	int nextChar = getc(stdin);
	while(nextChar != EOF){}
		if(input = malloc(BUFF_SIZE)){
			char buffer[BUFF_SIZE] = nextChar;
			int counter = 1;
			while(nextChar != EOF && nextChar != '\n'){
				counter++;
				nextChar = getc(stdin);
				if((counter-1) < BUFF_SIZE){
					buffer[counter-1] = nextChar;
				}
			}
			nextChar = getc(stdin);
			if(count <= BUFF_SIZE){
				strcpy(input, buffer);
				EnqueueString(queue1, input);
			}
		}
	}
}

// Scan line and replace each space ' ' with '*'
// Passes this line to munch2 through a queue
void *munch1(void *arg){
	char *input = "";
	while(input != NULL){
		input = DequeueString(queue1);
		if(input != NULL){
			char buffer[BUFF_SIZE];
			strcpy(buffer, input);
			int i;
			for(i = 0; i < BUFF_SIZE; i++){
				if(buffer[i] == ' '){
					buffer[i] = '*';
				}
			}
			strcpy(input,buffer);
		}
		EnqueueString(queue2, input);
	}
}

// Scan line and convert all lowercase to uppercase
// pass line to writer through a queue
void *munch2(void *arg){
	char *input = "";
	while(input != NULL){
		input = DequeueString(queue2);
		if(input != NULL){
			char buffer[BUFF_SIZE];
			strcpy(buffer, input);
			int i;
			for(i = 0; i < BUFF_SIZE; i++){
				if(islower(buffer[i]){
					int c = buffer[i];
					buffer[i] = toupper(c);
				}
			}
			strcpy(input,buffer);
		}
		EnqueueString(queue3, input);
	}
}

// write line to stdio
void *writer(void *arg){
	char *input = "";
	while(input != NULL){
		input = DequeueString(queue3);
		if(input != NULL){
			printf("%s\n", input);
			free(input);
		}
	}
}

int main(){
	if(!(sem_init(&resource, 0, 1)) && !(sem_init(&writer, 0, 1)) && !(sem_init(&reader, 0, 1))){
		// make queues
		Queue *q1 = CreateStringQueue(QUEUE_SIZE);
		Queue *q2 = CreateStringQueue(QUEUE_SIZE);
		Queue *q3 = CreateStringQueue(QUEUE_SIZE);
		// make threads
		pthread_create(&read, NULL, reader, NULL);
		pthread_create(&mun1, NULL, munch1, NULL);
		pthread_create(&mun2, NULL, munch2, NULL);
		pthread_create(&writ, NULL, writer, NULL);
		// join with terminated threads
		pthread_join(read, NULL);
		pthread_join(mun1, NULL);
		pthread_join(mun2, NULL);
		pthread_join(writ, NULL);
		// free resources
		sem_destroy(&resource);
		sem_destory(&writer);
		sem_destory(&reader);
	}
	return 0;
}
