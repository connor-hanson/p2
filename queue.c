#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "queue.h"

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

    // list is of char*, do not lose pointer. tail is dequeued
    queue->firstMem = malloc(size * sizeof(char*));

    if (queue->firstMem == NULL) {
        printf("Error allocating memory to queue data");
        return NULL;
    }

    // assigned later
    queue->head = NULL;
    queue->tail = NULL; 

    queue->numEntries = 0;
    queue->capacity = size;
    queue->enqueueCount = 0;
    queue->dequeueCount = 0;
    queue->enqueueTime = 0;
    queue->dequeueTime = 0;

    // return ptr to new queue structure
    return queue;
}

// places the pointer to the string at the end of the queue. 
// If the queue is full, block until space is available
void enqueueString(Queue *q, char *string) {
    //sem_wait(&resource);
    // if the queue is full, wait
    if (q->numEntries == q->capacity) {
        return; // FIXME
        //sem_post(&resource);
        //sem_wait(&writer);
    }

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
    //q->tail = malloc(sizeof(string));
    *(q->tail) = string;

    q->numEntries += 1;
    q->enqueueCount += 1;
    return;


    // // lock is free
    // if (q->numEntries == 0) {
    //     // do nothing, pointer stays where it is, but is now allocated to data
    //     //q->head = q->data; // set initial pointer
    // } else {
    //     //q->head = q->head + sizeof(char**); // increment to the next pointer
    //     (q->head)++;
    // }

    // // malloc string, ptr to char*
    // q->head = malloc(sizeof(string));
    // if (q->head == NULL) {
    //     // find way to cleanly shutdown program without exit(0)
    //     // better fucking work ig
    //     // printf not necessarily the best option for threaded programs
    //     perror("Memory allocation of string failed");
    //     // error
    // }

    // // now deref ptr and set its val
    // *(q->head) = string;

    // // change fields
    // q->numEntries += 1;
    // q->enqueueCount += 1;
    // // figure something out for time

    // //sem_post(&resource);
    // //sem_post(&reader);
}

//TODO: actual code lol
char *dequeueString(Queue *q) {
    //sem_wait(&resource);
    // if queue is empty, wait
    if(q->numEntries == 0) {
        return NULL; // FIXME when synchronization implemented
        //sem_post(&resource);
        //sem_wait(&reader);
    }
    char *retStr = *(q->tail);

    // free memory BEFORE losing ptr
    //printf("ayy");
    //free(q->head);
    // queue is no longer empty, dequeue string by size of string being removed
    //q->head = q->head - sizeof(char**);
    // tail has reached beginning of alloc'd memory
    if (q->numEntries != 1) { 
        if (q->tail == q->firstMem) {
            q->tail = q->firstMem + (q->capacity - 1) * sizeof(char*);
        } else {
            q->tail = q->tail - sizeof(char*);
        }
    }
    q->numEntries -= 1;
    q->dequeueCount += 1;
    //sem_post(&resource);
    //sem_post(&writer);
    
    return retStr;
}

void printQueueStats(Queue *q) {
    printf("%s\n", "Queue Statistics: ");
    printf("%s%d\n", "Number of entries: ", q->numEntries);
    printf("%s%d\n", "Capacity: ", q->capacity);
    printf("%s%d\n", "Enqueue Count: ", q->enqueueCount);
    printf("%s%d\n", "Dequeue Count: ", q->dequeueCount);
    printf("%s%d\n", "Enqueue Time: ", q->enqueueTime);
    printf("%s%d\n", "Dequeue Time: ", q->dequeueTime);
}
