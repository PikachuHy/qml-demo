//
// Created by pikachu on 2019/7/18.
//

#ifndef DATASTRUCTURES_ARRAYQUEUE_H
#define DATASTRUCTURES_ARRAYQUEUE_H
#include <stdbool.h>
struct ArrayQueueRecord;
typedef struct ArrayQueueRecord *ArrayQueue;
typedef int ElementType;
bool ArrayQueue_IsEmpty(ArrayQueue Q);
bool ArrayQueue_IsFull(ArrayQueue Q);
ArrayQueue CreateArrayQueue(int MaxElements);
void DisposeArrayQueue(ArrayQueue Q);
void ArrayQueue_MakeEmpty(ArrayQueue Q);
void ArrayQueue_Enqueue(ElementType X, ArrayQueue Q);
ElementType ArrayQueue_Front(ArrayQueue Q);
void ArrayQueue_Dequeue(ArrayQueue Q);
ElementType ArrayQueue_FrontAndDequeue(ArrayQueue Q);
char* ArrayQueue_ToString(ArrayQueue Q);
#endif //DATASTRUCTURES_ARRAYQUEUE_H
