//
// Created by pikachu on 2019/7/29.
//

#include "BinHeap.h"
#include "debug.h"
#include <stdlib.h>
#include <string.h>
#define MinPQSize 3
#define MinData -1
struct HeapStruct {
    int Capacity;
    int Size;
    ElementType *Elements;
};

PriorityQueue Initialize(int MaxElements) {
    PriorityQueue H;
    if (MaxElements < MinPQSize) {
        Fatal("Priority Queue size is too small\n");
        exit(1);
    }
    H = malloc(sizeof(struct HeapStruct));
    if (H == NULL) {
        Fatal("Out of space!!!\n");
        exit(1);
    }
    // Allocate the array plus one extra for sentinel;
    H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
    if (H->Elements == NULL) {
        Fatal("Out of space!!!\n");
        exit(1);
    }

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;

    return H;
}

void Insert(ElementType X, PriorityQueue H) {
    // H->Elements[0] is a sentinel
    int i;
    if (IsFull(H)) {
        Error("Priority queue is full\n");
        exit(1);
    }
    for (i = ++H->Size; H->Elements[i/2] > X; i/=2) {
        H->Elements[i] = H->Elements[i/2];
    }
    H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H) {
    int i, Child;
    ElementType MinElement, LastElement;

    if(IsEmpty(H)) {
        Error("Priority queue is empty\n");
        exit(1);
    }
    MinElement = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for (i = 1; i * 2 <= H->Size; i = Child) {
        // Find smaller child
        Child = i * 2;
        if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child]) {
            Child++;
        }
        // Percolate one level
        if (LastElement > H->Elements[Child]) {
            H->Elements[i] = H->Elements[Child];
        } else {
            break;
        }
    }
    H->Elements[i] = LastElement;
    return MinElement;
}

char *ToString(PriorityQueue H) {
    char str[1000] = "";
    for (int i = 0; i < H->Size; ++i) {
        sprintf(str, "%s,%d", str, H->Elements[i+1]);
    }
    char *ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}

bool IsEmpty(PriorityQueue H) {
    return H->Size == 0;
}

bool IsFull(PriorityQueue H) {
    return H->Size == H->Capacity;
}
