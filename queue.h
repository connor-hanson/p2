#ifndef QUEUE_H
#define QUEUE_H

typedef struct {

    char **head; // pointer to str at top of q
    int numEntries;
    int capacity;

    int enqueueCount;
    int dequeueCount;
    int enqueueTime;
    int dequeueTime;
} Queue;

Queue *createStringQueue(int size);
void enqueueString(Queue *q, char *string);
char * dequeueString(Queue *q);
void printQueueStats(Queue *q);

#endif