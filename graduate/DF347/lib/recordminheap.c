//
// Created by PikachuHy on 2019/10/18.
//

#include "recordminheap.h"
#include "memorypool.h"
#include <stdlib.h>
#include <stdio.h>
struct __RecordMinHeap {
    int size;
    int capacity;
    Record **list;
};
static Record * deleteMin(RecordMinHeap H) {
    int i, child;
    Record * minElement = H->list[1];
    Record * lastElement = H->list[H->size--];
    for(i = 1; i * 2 <= H->size; i = child) {
        child = i * 2;
        if (child != H->size && H->list[child+1]->extendedprice < H->list[child]->extendedprice) {
            child++;
        }
        if (lastElement->extendedprice > H->list[child]->extendedprice) {
            H->list[i] = H->list[child];
        } else {
            break;
        }
    }
    H->list[i] = lastElement;
    return minElement;
}
RecordMinHeap Record_CreateMinHeap(int maxElements) {
    RecordMinHeap H = GetMemory(sizeof(struct __RecordMinHeap)/ sizeof(int));
    H->size = 0;
    H->capacity = maxElements;
    H->list = (Record **) GetMemory(sizeof(Record *) / sizeof(int) * (maxElements + 1));
    Record *minRecord = (Record *) GetMemory(sizeof(Record) / sizeof(int));
    minRecord->extendedprice = -1;
    H->list[0] = minRecord;
    return H;
}

void Record_Insert(RecordMinHeap H, Record *record) {
    if (H->size == H->capacity) {
        if (record->extendedprice < H->list[1]->extendedprice)
            return;
        deleteMin(H);
    }
    int i;
    for(i = ++H->size;H->list[i/2]->extendedprice > record->extendedprice;i/=2) {
        H->list[i] = H->list[i/2];
    }
    H->list[i] = record;
}

Record *Record_FindMin(RecordMinHeap H) {
    if (H->size > 0) return H->list[1];
    return NULL;
}

Record *Record_DeleteMin(RecordMinHeap H) {
    if (H->size == 0) {
        printf("ERROR: Heap is empty.\n");
        exit(1);
    }
    return deleteMin(H);
}

void Record_DisposeMinHeap(RecordMinHeap H) {

}

bool Record_IsEmpty(RecordMinHeap H) {
    return H->size == 0;
}
