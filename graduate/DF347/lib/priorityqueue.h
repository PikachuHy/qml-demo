//
// Created by PikachuHy on 2019/10/17.
//

#ifndef DF347_PRIORITYQUEUE_H
#define DF347_PRIORITYQUEUE_H
typedef struct __PriorityQueue * PriorityQueue;

PriorityQueue CreatePriorityQueue(int len, int (*cmp)(void*, void*), int MaxElements, void* minValue);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(PriorityQueue H, void *X);
void * DeleteMin(PriorityQueue H);
void * FindMin(PriorityQueue H);
#endif //DF347_PRIORITYQUEUE_H
