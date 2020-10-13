#ifndef QUEUE_H
#define QUEUE_H

#include <semaphore.h>

typedef struct {

    char **head; // pointer to str at top of q
    char **tail;
    char **firstMem;
    int numEntries;
    int capacity;

    int enqueueCount;
    int dequeueCount;
    double enqueueTime;
    double dequeueTime;
    
    sem_t resource;
    sem_t full;
    sem_t empty;
} Queue;

Queue *createStringQueue(int size);
void enqueueString(Queue *q, char *string);
char * dequeueString(Queue *q);
void printQueueStats(Queue *q);
void freeQueue(Queue *q);

#endif
