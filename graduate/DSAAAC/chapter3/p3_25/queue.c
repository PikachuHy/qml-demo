//
// Created by pikachu on 2019/7/18.
//

#include "queue.h"
#include "debug.h"
#include <stdlib.h>
#include <string.h>
typedef struct Node * PtrToNode;
struct Node {
    ElementType Element;
    PtrToNode Next;
};
struct QueueRecord {
    int Capacity;
    PtrToNode Front;
    PtrToNode Rear;
    int Size;
};
PtrToNode newNode(ElementType X) {
    PtrToNode ret;
    ret = malloc(sizeof(struct Node));
    ret->Next = NULL;
    ret->Element = X;
    return ret;
}
Queue CreateQueue(int MaxElements) {
    Queue ret;
    ret = malloc(sizeof(struct QueueRecord));
    ret->Capacity = MaxElements;
    ret->Front = NULL;
    ret->Rear = NULL;
    ret->Size = 0;
    return ret;
}
bool IsFull(Queue Q) {
    return Q->Size == Q->Capacity;
}
bool IsEmpty(Queue Q) {
    return Q->Size == 0;
}
void Enqueue(ElementType X, Queue Q) {
    if (IsFull(Q)) {
        Fatal("Full queue");
        exit(1);
    }
    PtrToNode TmpCell = newNode(X);
    if(IsEmpty(Q)) {
        Q->Rear = TmpCell;
        Q->Front = TmpCell;
    } else {
        Q->Rear->Next = TmpCell;
        Q->Rear = TmpCell;
    }
    Q->Size ++;
}
void Dequeue(Queue Q) {
    if (IsEmpty(Q)) {
        Fatal("Empty queue\n");
        exit(1);
    }
    PtrToNode TmpCell = Q->Front;
    // Consider queue size == 1
    if (Q->Rear == Q->Front) {
        Q->Rear = NULL;
        Q->Front = NULL;
    } else {
        Q->Front = Q->Front->Next;
    }
    free(TmpCell);
    Q->Size -- ;
}

ElementType Front(Queue Q) {
    return Q->Front->Element;
}

char* ToString(Queue Q) {
    char str[1000] = "";
    PtrToNode it;
    it = Q->Front;
    while (it!= NULL) {
        sprintf(str, "%s%d<-", str, it->Element);
        it = it->Next;
    }
    char* ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}