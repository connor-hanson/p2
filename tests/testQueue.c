#include "../queue.h"
#include <stdlib.h>
#include <stdio.h>

int testQueueAlloc() {
    Queue *q = createStringQueue(10);
    if (q == NULL) {
        return -1;
    } else {
        return 1;
    }
}

int main() {
    if (testQueueAlloc() == -1) {
        printf("testQueueAlloc() failed");
    }
    return 0;
}