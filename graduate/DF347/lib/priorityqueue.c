//
// Created by PikachuHy on 2019/10/17.
//

#include "priorityqueue.h"
#include "memorypool.h"
#include <stdlib.h>
#include <stdio.h>

//struct __PriorityQueue {
struct __PriorityQueue {
    int capacity;
    int size;
    int typeLength;
    int (*cmp)(void *a, void *b);
    void **elements;
};

PriorityQueue CreatePriorityQueue(int len, int (*cmp)(void*, void*), int MaxElements, void* minValue) {
    PriorityQueue H;
    H = GetMemory(sizeof(struct __PriorityQueue)/ sizeof(int));
    H->capacity = MaxElements;
    H->size = 0;
    H->typeLength = len;
    H->cmp = cmp;
    H->elements = GetMemory(H->typeLength/ sizeof(int) * (MaxElements + 1));
    H->elements[0] = minValue;
    return H;
}

void Destroy(PriorityQueue H) {
    free(H->elements);
    free(H);
}

void Insert(PriorityQueue H, void *X) {
    printf("DEBUG: Insert %d\n", *(int*)X);
    int i = 0;
    for (i = ++H->size; H->cmp(X, H->elements[i/2 * H->typeLength]) < 0; i /= 2) {
        H->elements[i * H->typeLength] = H->elements[i / 2 * H->typeLength];
        printf("DEBUG: Down %d\n", *(int*)H->elements[i/2 * H->typeLength]);
    }
    H->elements[i * H->typeLength] = X;
    printf("DEBUG: %d\n", *(int*)H->elements[1 * H->typeLength]);
}

void * DeleteMin(PriorityQueue H) {
    int i, Child;
    void * MinElement;
    void *LastElement;
    MinElement = H->elements[1];
    LastElement = H->elements[H->size--];

    for (i = 1; i * 2 <= H->size; i = Child) {
        Child = i * 2;
        if (Child != H->size && H->cmp(H->elements[Child + 1], H->elements[Child]) < 0)
            Child++;
        if (H->cmp(H->elements[Child], LastElement))
            H->elements[i] = H->elements[Child];
        else
            break;
    }
    H->elements[i] = LastElement;
    return MinElement;
}

void *FindMin(PriorityQueue H) {
    if (H->size > 0) return H->elements[1 * H->typeLength];
    return NULL;
}
