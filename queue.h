#ifndef QUEUE_H
#define QUEUE_H

typedef struct {} Queue;

Queue *createStringQueue(int size);
void enqueueString(Queue *q, char *string);
char * dequeueString(Queue *q);
void printQueueStats(Queue *q);

#endif