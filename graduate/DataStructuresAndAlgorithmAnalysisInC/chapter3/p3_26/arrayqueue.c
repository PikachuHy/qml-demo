//
// Created by pikachu on 2019/7/21.
//

#include "deque.h"
#include "debug.h"
#include <stdlib.h>
#include <string.h>
#define MinQueueSize (5)

struct QueueRecord {
    int Capacity;
    int Front;
    int Rear;
    ElementType *Array;
};
bool IsEmpty(Deque D) {
    return D->Front == D->Rear;
}
bool IsFull(Deque D) {
    return (D->Rear + 1) % D->Capacity == D->Front;
}
Deque CreateDeque(int MaxElements) {
    Deque ret;
    ret = malloc(sizeof(struct QueueRecord));
    ret->Capacity = MaxElements;
    ret->Rear = 0;
    ret->Front = 0;
    ret->Array = malloc(sizeof(ElementType) * ret->Capacity);
    return ret;
}
void DisposeDeque(Deque D) {
    free(D->Array);
    free(D);
}
void Push(ElementType X, Deque D) {
    D->Front = (D->Front + D->Capacity - 1) % D->Capacity;
    D->Array[D->Front] = X;
}
void Pop(Deque D) {
    D->Front = (D->Front + 1) % D->Capacity;
}
void Inject(ElementType X, Deque D) {
    D->Array[D->Rear] = X;
    D->Rear = (D->Rear + 1) % D->Capacity;
}
void Eject(Deque D) {
    D->Rear = (D->Rear + D->Capacity -1) % D->Capacity;
}
ElementType Front(Deque D) {
    return D->Array[D->Front];
}
int Size(Deque D) {
    if (D->Rear < D->Front) {
        return D->Rear + D->Capacity - D->Front;
    } else {
        return D->Rear - D->Front;
    }
}
char* ToString(Deque D) {
    char str[1000] = "";
    for (int i = 0; i < Size(D); ++i) {

        ElementType data = D->Array[(i + D->Front) % D->Capacity];
        sprintf(str, "%s%d<-", str, data);
    }
    char *ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}