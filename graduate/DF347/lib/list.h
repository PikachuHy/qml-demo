//
// Created by PikachuHy on 2019/10/16.
//

#ifndef DF347_LIST_H
#define DF347_LIST_H

#include "memorypool.h"
struct ListNode {
    int Data;
    struct ListNode *Next;
};
typedef struct ListNode *List;
#define NEW_LIST_NODE ((struct ListNode *) GetMemory(sizeof(struct ListNode)/sizeof(int)))
#define InsertData(list, data) { \
    struct ListNode * NewNode = NEW_LIST_NODE; \
    NewNode->Data = data; \
    NewNode->Next = list->Next; \
    list->Next = NewNode;\
}
struct PtrNode {
    void *Data;
    struct PtrNode *Next;
};
typedef struct PtrNode *PtrList;

#define NEW_PTR_LIST_NODE ((struct PtrNode *) GetMemory(sizeof(struct PtrNode)/sizeof(int)))
#define InsertPtr(list, data) { \
    struct PtrNode * NewNode = NEW_PTR_LIST_NODE; \
    NewNode->Data = data; \
    NewNode->Next = list->Next; \
    list->Next = NewNode;\
}
#endif //DF347_LIST_H
