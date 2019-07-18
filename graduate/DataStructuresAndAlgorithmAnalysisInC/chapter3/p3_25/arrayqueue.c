//
// Created by pikachu on 2019/7/18.
//

#include "arrayqueue.h"
#include "debug.h"
#include <stdlib.h>
#include <string.h>
#define MinQueueSize (5)

struct ArrayQueueRecord {
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

ArrayQueue CreateArrayQueue(int MaxElements) {
    if (MaxElements <= 0) {
        Fatal("MaxElements must >= 0\n");
        exit(1);
    }
    ArrayQueue ret;
    ret = malloc(sizeof(struct ArrayQueueRecord));
    ret->Capacity = MaxElements;
    ret->Array = malloc(sizeof(ElementType) * ret->Capacity);
    ArrayQueue_MakeEmpty(ret);
    return ret;
}
bool ArrayQueue_IsEmpty(ArrayQueue Q) {
    return Q->Size == 0;
}
void ArrayQueue_MakeEmpty(ArrayQueue Q) {
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

static int Succ(int value, ArrayQueue Q) {
    if (++value == Q->Capacity) {
        value = 0;
    }
    return value;
}

void ArrayQueue_Enqueue(ElementType X, ArrayQueue Q) {
    if (ArrayQueue_IsFull(Q)) {
        Fatal("Full queue\n");
        exit(1);
    } else {
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

void ArrayQueue_Dequeue(ArrayQueue Q) {
    if (ArrayQueue_IsEmpty(Q)) {
        Fatal("Empty queue\n");
        exit(1);
    } else {
        Q->Size --;
        Q->Front = Succ(Q->Front, Q);
    }
}
char* ArrayQueue_ToString(ArrayQueue Q) {
    char str[1000] = "";
    if (!ArrayQueue_IsEmpty(Q)) {
        int i = Q->Front - 1;
        do {
            i = (i + 1) % Q->Capacity;
            sprintf(str, "%s%d<-", str, Q->Array[i]);
        }while (i != Q->Rear);
    }
    char* ret;
    ret= malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}
ElementType ArrayQueue_Front(ArrayQueue Q) {
    if (ArrayQueue_IsEmpty(Q)) {
        Fatal("Empty queue\n");
        exit(1);
    }
    return Q->Array[Q->Front];
}
bool ArrayQueue_IsFull(ArrayQueue Q) {
    return Q->Size == Q->Capacity;
}