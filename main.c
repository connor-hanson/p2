//Author: Connor Hanson, Tiger Ji

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "queue.h"
#include "pthreadDef.h"
#include "queueStat.h"

#define QUEUE_SIZE 10

pthread_t read, mun1, mun2, writ;

static Queue *q1;
static Queue *q2;
static Queue *q3;

int main(){
	// make queues, exit on failure
	q1 = createStringQueue(QUEUE_SIZE);
	q2 = createStringQueue(QUEUE_SIZE);
	q3 = createStringQueue(QUEUE_SIZE);
	if(q1 != NULL && q2 != NULL && q3 != NULL){
		// group queues to pass to thread funcs, exit on failure
		Queue **readMunch = malloc(2*sizeof(Queue *));
		Queue **munchMunch = malloc(2*sizeof(Queue *));
		if(readMunch == NULL || munchMunch == NULL){
			exit(EXIT_FAILURE);
		}
		readMunch[0] = q1;
		readMunch[1] = q2;
		munchMunch[0] = q2;
		munchMunch[1] = q3;
		// make threads, exit on failure
		if(pthread_create(&read, NULL, reader, q1)){
			exit(EXIT_FAILURE);
		}
		if(pthread_create(&mun1, NULL, munch1, readMunch)){
			exit(EXIT_FAILURE);
		}
		if(pthread_create(&mun2, NULL, munch2, munchMunch)){
			exit(EXIT_FAILURE);
		}
		if(pthread_create(&writ, NULL, writer, q3)){
			exit(EXIT_FAILURE);
		}
		// join with terminated threads
		pthread_join(read, NULL);
		pthread_join(mun1, NULL);
		pthread_join(mun2, NULL);
		pthread_join(writ, NULL);
		// print stderr stats
		fprintf(stderr, "Queue 1 Statistics:\n");
		printQueueStats(q1);
		fprintf(stderr, "Queue 2 Statistics:\n");
		printQueueStats(q2);
		fprintf(stderr, "Queue 3 Statistics:\n");
		printQueueStats(q3);
		// free queue groups
		free(readMunch);
		free(munchMunch);
		// free queue elements
		freeQueue(q1);
		freeQueue(q2);
		freeQueue(q3);
		// free queues
		free(q1);
		free(q2);
		free(q3);
	}
	else{
		exit(EXIT_FAILURE);
	}
	return 0;
}
