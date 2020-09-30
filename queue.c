#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char **data; // entirety of array of strings
    char **head; // pointer to last added string
    int numEntries;
    int capacity; 

    int enqueueCount;
    int dequeueCount;
    int enqueueTime;
    int dequeueTime;
} Queue;

//Dynamically allocate a new Queue structure and initialize it with an array of character points of length size. 
//That means you'll malloc the queue structure and then malloc the char ** array pointed to from that structure. 
//Also remember to any state and synchronization variables used in this structure.
//The function returns a pointer to the new queue structure.
// Test with size 10
// TODO: add synchronization
Queue *createStringQueue(int size) {
    Queue *queue = malloc(sizeof(Queue));

    if (queue == NULL) {
        printf("Error allocating memory to Queue**");
        return NULL;
    }

    queue->data = malloc(size * sizeof(char**));
    if (queue->data == NULL) {
        printf("Error allocating memory to queue data");
        return NULL;
    }

    queue->numEntries = 0;
    queue->capacity = size;
    queue->head = NULL; // not defined

    return queue;
}

// places the pointer to the string at the end of the queue. 
// If the queue is full, block until space is available
void enqueueString(Queue *q, char *string) {
    if (q->numEntries == q->capacity) {
        // lock
    }
    // lock is free
    if (q->numEntries == 0) {
        q->head = q->data; // set initial pointer
    } else {
        q->head = q->head + sizeof(char**); // increment to the next pointer
    }

    q->numEntries += 1;
}

char *dequeueString(Queue *q) {
    return NULL;
}

void printQueueStats(Queue *q) {
}