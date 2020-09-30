#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *head;
    char *tail;
    char **data;
    int numEntries;

} Queue;

//Dynamically allocate a new Queue structure and initialize it with an array of character points of length size. 
//That means you'll malloc the queue structure and then malloc the char ** array pointed to from that structure. 
//Also remember to any state and synchronization variables used in this structure.
//The function returns a pointer to the new queue structure.
// Test with size 10
Queue *createStringQueue(int size) {
    Queue *queue = malloc(sizeof(Queue));

    if (queue == NULL) {
        printf("Error allocating memory to Queue**");
        return NULL;
    }

    queue->data = malloc(size * sizeof(char*));
    if (queue->data == NULL) {
        printf("Error allocating memory to queue data");
        return NULL;
    }

    queue->numEntries = 0;

    return queue;
}

void enqueueString(Queue *q, char *string) {
}

char *dequeueString(Queue *q) {
    return NULL;
}

void printQueueStats(Queue *q) {
}