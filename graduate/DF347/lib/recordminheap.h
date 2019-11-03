//
// Created by PikachuHy on 2019/10/18.
//

#ifndef DF347_RECORDMINHEAP_H
#define DF347_RECORDMINHEAP_H

#include "aggregation.h"
#include <stdbool.h>
typedef struct __RecordMinHeap * RecordMinHeap;
RecordMinHeap Record_CreateMinHeap(int maxElements);
void Record_Insert(RecordMinHeap H, Record *record);
Record* Record_FindMin(RecordMinHeap H);
Record* Record_DeleteMin(RecordMinHeap H);
bool Record_IsEmpty(RecordMinHeap H);
void Record_DisposeMinHeap(RecordMinHeap H);
#endif //DF347_RECORDMINHEAP_H
