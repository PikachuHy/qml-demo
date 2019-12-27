//
// Created by pikachu on 2019/7/21.
//

#ifndef DATASTRUCTURES_DEQUE_H
#define DATASTRUCTURES_DEQUE_H

#include <stdbool.h>
struct QueueRecord;
typedef struct QueueRecord* Deque;
typedef int ElementType;
bool IsEmpty(Deque D);
bool IsFull(Deque D);
Deque CreateDeque(int MaxElements);
void DisposeDeque(Deque Q);
void Push(ElementType X, Deque D);
void Pop(Deque D);
void Inject(ElementType X, Deque D);
void Eject(Deque D);
ElementType Front(Deque D);
int Size(Deque D);
char* ToString(Deque Q);
#endif //DATASTRUCTURES_DEQUE_H
