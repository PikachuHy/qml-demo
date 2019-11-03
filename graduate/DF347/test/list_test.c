//
// Created by PikachuHy on 2019/10/17.
//

#include "test.h"
#include "list.h"

int test1() {
    InitMemoryPool();
    struct ListNode * list = GetMemory(sizeof(struct ListNode));
    InsertData(list , 1)
    ASSERT_INT_EQUAL(list->Next->Data, 1)
    InsertData(list, 2)
    ASSERT_INT_EQUAL(list->Next->Data, 2)
    struct ListNode *it = list->Next;
    while (it) {
        printf("%d\n", it->Data);
        it = it->Next;
    }
    DisposeMemoryPool();
    return 0;
}

int main() {
    InitMemoryPool();
    PtrList list = GetMemory(sizeof(struct PtrNode)/ sizeof(int));
    int *a = GetMemory(1);
    *a = 1;
    InsertPtr(list, a);
    ASSERT_INT_EQUAL(*(int*)(list->Next->Data), *a)
    DisposeMemoryPool();
    return 0;
}