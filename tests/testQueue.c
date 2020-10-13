#include "../queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// tests without syncronization
int testQueueAlloc() {
    Queue *q = createStringQueue(10);
    // test for error allocating initial queue ptr
    if (q == NULL) {
        printf("queue ptr is null \n");
        return -1;
    } 
    
    // test data allocation, redundant but still
    if (q->firstMem == NULL) {
        printf("firstMem is null \n");
        return -1;
    }

    free(q);
    // freeme
    return 1;
}

// obsolete when threading added but whatever
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
    if (strcmp(*(q->tail), str1) != 0) {
        printf("%s%s%s\n", "String ", str1, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str2);
    if (strcmp(*(q->tail), str2) != 0) {
        printf("%s%s%s\n", "String ", str2, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str3);
    if (strcmp(*(q->tail), str3) != 0) {
        printf("%s%s%s\n", "String ", str3, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str4);
    if (strcmp(*(q->tail), str4) != 0) {
        printf("%s%s%s\n", "String ", str4, " should have been added to q but was not");
        return -1;
    }
    enqueueString(q, str5);
    if (strcmp(*(q->tail), str5) != 0) {
        printf("%s%s%s\n", "String ", str5, " should have been added to q but was not");
        return -1;
    }

    for (int i = 0; i < 5; ++i) {
        char *str = "connoriscool";
        enqueueString(q, str);
        if (strcmp(*(q->tail), str) != 0) {
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
    Queue *q = createStringQueue(10);
    // assume shit works

    // fill to capacity
    for (int i = 0; i < 10; ++i) {
        char *str = "yo";
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // make each string queued up unique
        enqueueString(q, strInt);
        if (strcmp(*(q->head), strInt) != 0) {
            printf("%s%d%s\n", "String #", i, " should have been added to q but was not");
            return -1;
        }
    }

    // now dequeue stuff till empty
    for (int i = 9; i >= 0; --i) {
        char* str = dequeueString(q);
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // add int to str
        if (strcmp(str, strInt) != 0) {
            printf("%s%s%s%s\n", "Dequeued str ", str, " is not the same as test str ", strInt);
            return -1;
        }
    }

    // try dequeue when empty
    char *str = dequeueString(q); 
    if (str != NULL) {
        printf("no string should have been dequeued");
        return -1;
    }

    return 1;
}

int testEnqueueAndDequeueNoSync() {
    Queue *q = createStringQueue(10);
    // enqueue 10
    for (int i = 0; i < 10; ++i) {
        char *str = "yo";
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // make each string queued up unique
        enqueueString(q, strInt);
        if (strcmp(*(q->head), strInt) != 0) {
            printf("%s%d%s\n", "String #", i, " should have been added to q but was not");
            return -1;
        }
    }

    // dequeue 5
    for (int i = 9; i >= 5; --i) {
        char* str = dequeueString(q);
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // add int to str
        if (strcmp(str, strInt) != 0) {
            printf("%s%s%s%s\n", "Dequeued str ", str, " is not the same as test str ", strInt);
            return -1;
        }
    }

    // enqueue 3
    for (int i = 5; i < 8; ++i) {
        char *str = "yo";
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // make each string queued up unique
        enqueueString(q, strInt);
        if (strcmp(*(q->head), strInt) != 0) {
            printf("%s%d%s\n", "String #", i, " should have been added to q but was not");
            return -1;
        }
    }

    // dequeue 8 (all)
    for (int i = 7; i >= 0; --i) {
        char* str = dequeueString(q);
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // add int to str
        if (strcmp(str, strInt) != 0) {
            printf("%s%s%s%s\n", "Dequeued str ", str, " is not the same as test str ", strInt);
            return -1;
        }
    }

    // enqueue 5
    for (int i = 0; i < 5; ++i) {
        char *str = "yo";
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // make each string queued up unique
        enqueueString(q, strInt);
        if (strcmp(*(q->head), strInt) != 0) {
            printf("%s%d%s\n", "String #", i, " should have been added to q but was not");
            return -1;
        }
    }

    // dequeue 3
    for (int i = 4; i >= 2; --i) {
        char* str = dequeueString(q);
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // add int to str
        if (strcmp(str, strInt) != 0) {
            printf("%s%s%s%s\n", "Dequeued str ", str, " is not the same as test str ", strInt);
            return -1;
        }
    }

    // enqueue to capacity (+8)
    for (int i = 2; i < 9; ++i) {
        char *str = "yo";
        char strInt[5];
        snprintf(strInt, 10, "%s%d", str, i); // make each string queued up unique
        enqueueString(q, strInt);
        if (strcmp(*(q->head), strInt) != 0) {
            printf("%s%d%s\n", "String #", i, " should have been added to q but was not");
            return -1;
        }
    }

    // try to enqueue. Should fail
    char *str = "should not work y0";
    enqueueString(q, str);
    if (strcmp(*(q->head), str) == 0) {
        printf("%s\n", "String should not have been enqueued. The queue must be getting confused");
        return -1;
    }

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

    if (testDequeueNoSync() == -1) {
        printf("Dequeueing string with no sync failed.\n");
    }

    if (testEnqueueAndDequeueNoSync() == -1) {
        printf("Enqueueing and dequeueing strings failed. shit. \n");
    }
    // else {
    //     printf("somehow no crash?");
    // }
    return 0;
}