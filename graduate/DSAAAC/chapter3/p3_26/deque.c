//
// Created by pikachu on 2019/7/21.
//

#include "deque.h"
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

Deque CreateDeque(int MaxElements) {
    Deque ret;
    ret = malloc(sizeof(struct QueueRecord));
    ret->Capacity = MaxElements;
    ret->Front = NULL;
    ret->Rear = NULL;
    ret->Size = 0;
    return ret;
}

void DisposeDeque(Deque Q) {

}
bool IsEmpty(Deque D) {
    return D->Size == 0;
}
bool IsFull(Deque D) {
    return D->Size == D->Capacity;
}
void Push(ElementType X, Deque D) {
    if (IsFull(D)) {
        Fatal("Deque is full\n");
        return;
    }
    PtrToNode tmpCell;
    tmpCell = newNode(X);
    if (IsEmpty(D)) {
        D->Rear = tmpCell;
    } else {
        tmpCell->Next = D->Front;
    }
    D->Front = tmpCell;
    D->Size ++;
}

void Pop(Deque D) {
    if(IsEmpty(D)) {
        Fatal("Deque is empty\n");
        return;
    }
    PtrToNode tmpCell;
    tmpCell = D->Front;
    if (D->Front == D->Rear) {
        D->Front = NULL;
        D->Rear = NULL;
    } else {
        D->Front = tmpCell->Next;
    }
    free(tmpCell);
    D->Size --;
}

void Inject(ElementType X, Deque D) {
    if (IsFull(D)) {
        Fatal("Deque is full\n");
        return;
    }
    PtrToNode tmpCell;
    tmpCell = newNode(X);
    if (D->Rear == NULL) {
        D->Front = tmpCell;
    } else {
        D->Rear->Next = tmpCell;
    }
    D->Rear = tmpCell;
    D->Size ++;
}

void Eject(Deque D) {
    if (IsEmpty(D)) {
        Fatal("Deque is empty\n");
        return;
    }
    PtrToNode tmpCell;
    tmpCell = D->Rear;
    if (D->Rear == D->Front) {
        D->Rear = NULL;
        D->Front = NULL;
    } else {
        // Require O(1)
        // But current implement is O(n)
        PtrToNode it;
        it = D->Front;
        while(it->Next != D->Rear) {
            it = it->Next;
        }
        D->Rear = it;
        D->Rear->Next = NULL;
    }
    free(tmpCell);
    D->Size --;
}
ElementType Front(Deque D) {
    if (IsEmpty(D)) {
        Fatal("Deque is empty\n");
        exit(1);
    }
    return D->Front->Element;
}
char* ToString(Deque D) {
    char str[1000] = "";
    PtrToNode it = D->Front;
    for (int i = 0; i < D->Size; ++i) {
        sprintf(str, "%s%d<-", str, it->Element);
        it = it->Next;
    }
    char *ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}