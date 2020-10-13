// Authors: Connor Hanson, Tiger Ji
// Connor Hanson: cbhanson2@wisc.edu - chanson
// Tiger Ji: tfji@wisc.edu - tfji

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "queue.h"
#include "queueStat.h"

/**
 * Prints queue stats
 *
 * @param:
 *	Queue *q - pointer to queue to have stats printed to stderr
 */
void printQueueStats(Queue *q){
	fprintf(stderr,"%s%d\n", "Capacity: ", q->capacity);
	fprintf(stderr,"%s%d\n", "Enqueue Count: ", q->enqueueCount -1);
	fprintf(stderr,"%s%d\n", "Dequeue Count: ", q->dequeueCount-1);
	fprintf(stderr,"%s%f\n", "Enqueue Time: ", q->enqueueTime);
	fprintf(stderr,"%s%f\n", "Dequeue Time: ", q->dequeueTime);
}

/**
 * Increments enqueue count
 *
 * @param:
 *	Queue *q - pointer to queue to have stat changed
 */
void incEnqueue(Queue *q){
	q->enqueueCount += 1;
}

/**
 * Increments dequeue count
 *
 * @param:
 *	Queue *q - pointer to queue to have stat changed
 */
void incDequeue(Queue *q){
	q->dequeueCount += 1;
}

/**
 * Increments entries count
 *
 * @param:
 *	Queue *q - pointer to queue to have stat changed
 */
void incEntries(Queue *q){
	q->numEntries += 1;
}

/**
 * Decrements entries count
 *
 * @param:
 *	Queue *q - pointer to queue to have stat changed
 */
void decEntries(Queue *q){
	q->numEntries -= 1;
}

/**
 * Adds to total enqueue time
 *
 * @param:
 *	Queue *q - pointer to queue to have stat changed
 */
void addETime(Queue *q, double time){
	q->enqueueTime += time;
}

/**
 * Adds to total dequeue time
 *
 * @param:
 *	Queue *q - pointer to queue to have stat changed
 */
void addDTime(Queue *q, double time){
	q->dequeueTime += time;
}
