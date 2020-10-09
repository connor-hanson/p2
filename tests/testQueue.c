#include "../queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// tests without syncronization
int testQueueAlloc() {
    Queue *q = createStringQueue(10);
    // test for error allocating initial queue ptr
    if (q == NULL) {
        return -1;
    } 
    
    // test data allocation, redundant but still
    if (q->head == NULL) {
        return -1;
    }

    return 1;
}

int testEnqueueNoSync() {
    Queue *q = createStringQueue(10);
    // assume allocation works

    char *str1 = "folks";
    char *str2 = "poopoo123";
    char *str3 = "";
    char *str4 = "\tyeet\t";
    char *str5 = "coffÍe";

    // test that memory pointed to by new head == respective string
    // q->head is char**, so *(q->head) is char*, ie string
    enqueueString(q, str1);
    if (strcmp(*(q->head), str1) != 0) {
        printf("%s%s%s\n", "String ", str1, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str2);
    if (strcmp(*(q->head), str2) != 0) {
        printf("%s%s%s\n", "String ", str2, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str3);
    if (strcmp(*(q->head), str3) != 0) {
        printf("%s%s%s\n", "String ", str3, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str4);
    if (strcmp(*(q->head), str4) != 0) {
        printf("%s%s%s\n", "String ", str4, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str5);
    if (strcmp(*(q->head), str5) != 0) {
        printf("%s%s%s\n", "String ", str5, " should have been added to q but was not");
        return -1;
    }

    for (int i = 0; i < 5; ++i) {
        char *str = "connoriscool";
        enqueueString(q, str);
        if (strcmp(*(q->head), str) != 0) {
            printf("%s%s%s\n", "String ", str, " should have been added to q but was not");
            return -1;
        }
    }
    // should throw no errors up to here

    char* str = "tigeriscool";
    enqueueString(q, str);
    // should not be equal, queue is at capacity
    if (strcmp(*(q->head), str) == 0) {
        printf("%s%s%s\n", "String ", str, " should not have been added to queue. Queue is at capacity");
        return -1;
    }

    return 1; // all is good in the world
}

int testDequeueNoSync() {
    return 0;
}

int testEnqueueAndDequeueNoSync() {
    return 0;
}

// tests with sync
int testEnqueueWithSync() {
    return 0;
}

int testDequeueWithSync() {
    return 0;
}

// main
int main() {
    if (testQueueAlloc() == -1) {
        printf("testQueueAlloc() failed");
    }

    if (testEnqueueNoSync() == -1) {
        printf("Enqueing strings with no sync failed. You suck lol \n");
    } 
    // else {
    //     printf("somehow no crash?");
    // }
    return 0;
}