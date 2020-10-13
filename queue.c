//Author: Connor Hanson, Tiger Ji

#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include "queue.h"
#include "queueStat.h"

/**
 * Create queue
 *
 * @param:
 *	int size - queue size/capacity
 * @returns:
 *	pointer to new Queue, or NULL if unsuccessful
 */
Queue *createStringQueue(int size) {
	Queue *queue = malloc(sizeof(Queue));

	if (queue == NULL) {
		printf("Error allocating memory to Queue**");
		return NULL;
	}

    	// list is of char*, do not lose pointer. tail is dequeued
    	queue->firstMem = malloc(size * sizeof(char*));

    	if (queue->firstMem == NULL) {
        	printf("Error allocating memory to queue data");
        	return NULL;
    	}

    	// assigned later
    	queue->head = NULL;
    	queue->tail = NULL; 
	// init queue stats
    	queue->numEntries = 0;
    	queue->capacity = size;
    	queue->enqueueCount = 0;
    	queue->dequeueCount = 0;
    	queue->enqueueTime = 0;
    	queue->dequeueTime = 0;
    	// return NULL if any sem initializes unsuccessfully
    	if(sem_init(&queue->resource, 0, 1)){
    		return NULL;
    	}
    	if(sem_init(&queue->full, 0, 0)){
    		return NULL;
    	}
    	if(sem_init(&queue->empty, 0, queue->capacity)){
    		return NULL;
    	}
    	
    	// return ptr to new queue structure
    	return queue;
}

/**
 * Enqueues string into queue
 *
 * @param:
 *	Queue *q - pointer to queue to alter
 *	char *string - string to be enqueued
 */
void enqueueString(Queue *q, char *string) {
	clock_t start = clock(); // Begin clock
    	sem_wait(&q->empty); // wait if queue full
    	sem_wait(&q->resource); // wait if queue is being changed
    	// move head/tail pointer to firstMem if empty
    	if (q->numEntries == 0) {
        	q->head = q->firstMem;
        	q->tail = q->firstMem;
    	} else {
        	// get check that tail is not at end of alloc'd memory
        	int memDiff = (q->tail - q->firstMem);
        	int okDiff = (q->capacity - 1) * sizeof(char*);

        	if (memDiff == okDiff) { // loop round to first byte of ok memory
            		q->tail = q->firstMem;
            		printf("resetting mem");
        	} else {
            		q->tail = q->tail + sizeof(char*); // increment by a ptr location. ++ should do this
       	}
    	}

    	// now allocate memory/string to tail
    	*(q->tail) = string;
	    // change queue stats
    	incEntries(q);
    	incEnqueue(q);
    	clock_t end = clock();
    	double spentTime = (double)(end - start)/CLOCKS_PER_SEC; // calc time taken
    	addETime(q, spentTime);
    	sem_post(&q->resource);
    	sem_post(&q->full); // release any waiting dequeues
}

/**
 * Dequeues string from queue
 *
 * @param:
 *	Queue *q - pointer to queue to alter
 * @returns:
 *	string dequeued
 */
char *dequeueString(Queue *q) {
	clock_t start = clock(); // begin clock
    	sem_wait(&(q->full)); // wait if queue empty
    	sem_wait(&(q->resource)); // wait if queue being changed
    	char *retStr = *(q->tail);
    	
    	if (q->numEntries != 1) { 
        	if (q->tail == q->firstMem) {
            		q->tail = q->firstMem + (q->capacity - 1) * sizeof(char*);
        	} else {
            		q->tail = q->tail - sizeof(char*);
        	}
    	}
    	// change queue stats
    	decEntries(q);
    	incDequeue(q);
    	clock_t end = clock();
    	double spentTime = (double)(end - start)/CLOCKS_PER_SEC; // calc time taken
    	addDTime(q, spentTime);
    	sem_post(&(q->resource));
    	sem_post(&(q->empty)); // release any waiting enqueues
    	return retStr;
}

/**
 * Frees allocated space from elements of queue
 *
 * @param:
 *	Queue *q - pointer to queue to free
 */
void freeQueue(Queue *q){
	free(q->firstMem); // free malloced firstMem
	sem_destroy(&q->resource); // free semaphors
	sem_destroy(&q->full);
	sem_destroy(&q->empty);
}
