#ifndef QUEUESTAT_H
#define QUEUESTAT_H

void printQueueStats(Queue *q);
void incEnqueue(Queue *q);
void incDequeue(Queue *q);
void incEntries(Queue *q);
void decEntries(Queue *q);
void addETime(Queue *q, double time);
void addDTime(Queue *q, double time);

#endif
