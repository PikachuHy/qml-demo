//
// Created by pikachu on 2019/7/29.
//

#ifndef DEMO_BINHEAP_H
#define DEMO_BINHEAP_H

#include <stdbool.h>
struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
typedef int ElementType;
PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
bool IsEmpty(PriorityQueue H);
bool IsFull(PriorityQueue H);
char* ToString(PriorityQueue H);
#endif //DEMO_BINHEAP_H
