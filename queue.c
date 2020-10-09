#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

typedef struct {
    //char **data; // entirety of array of strings
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

    // returns pointer to where head of list should be, do not lose pointer
    queue->head = malloc(size * sizeof(char**));
    if (queue->head == NULL) {
        printf("Error allocating memory to queue data");
        return NULL;
    }

    queue->numEntries = 0;
    queue->capacity = size;

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
    // lock is free
    if (q->numEntries == 0) {
        // do nothing, pointer stays where it is, but is now allocated to data
        //q->head = q->data; // set initial pointer
    } else {
        q->head = q->head + sizeof(char**); // increment to the next pointer
    }

    // malloc string, ptr to char*
    q->head = malloc(sizeof(string));
    if (q->head == NULL) {
        // find way to cleanly shutdown program without exit(0)
        // better fucking work ig
        // printf not necessarily the best option for threaded programs
        perror("Memory allocation of string failed");
        // error
    }

    // now deref ptr and set its val
    *(q->head) = string;

    // change fields
    q->numEntries += 1;
    q->enqueueCount += 1;
    // figure something out for time

    //sem_post(&resource);
    //sem_post(&reader);
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
    char *retStr = *(q->head);

    // free memory BEFORE losing ptr
    printf("ayy");
    free(q->head);
    // queue is no longer empty, dequeue string by size of string being removed
    q->head = q->head - sizeof(char**);
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
