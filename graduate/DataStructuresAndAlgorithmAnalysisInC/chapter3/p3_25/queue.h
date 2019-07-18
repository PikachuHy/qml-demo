//
// Created by pikachu on 2019/7/18.
//

#ifndef DATASTRUCTURES_QUEUE_H
#define DATASTRUCTURES_QUEUE_H

#include <stdbool.h>
struct QueueRecord;
typedef struct QueueRecord* Queue;
typedef int ElementType;
bool IsEmpty(Queue Q);
bool IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue();
void Enqueue(ElementType X, Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);
char* ToString(Queue Q);
#endif //DATASTRUCTURES_QUEUE_H
