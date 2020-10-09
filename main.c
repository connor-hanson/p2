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

static Queue *queue1;
static Queue *queue2;
static Queue *queue3;

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
		queue1 = CreateStringQueue(QUEUE_SIZE);
		queue2 = CreateStringQueue(QUEUE_SIZE);
		queue3 = CreateStringQueue(QUEUE_SIZE);
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
