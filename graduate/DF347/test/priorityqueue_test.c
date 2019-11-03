//
// Created by PikachuHy on 2019/10/17.
//
#include <limits.h>
#include "test.h"
#include "memorypool.h"
#include "priorityqueue.h"
int cmp(void *a, void *b) {
    return (*(int*)a) - (*(int*)b);
}
int main() {
    InitMemoryPool();
    int minValue = -10;
    PriorityQueue H = CreatePriorityQueue(sizeof(int), cmp, 5, &minValue);
    for (int i = 10; i > 0; --i) {
        int *x = GetMemory(1);
        *x = i;
        Insert(H, x);
        ASSERT_INT_EQUAL(*(int*)FindMin(H), i)
    }
    DisposeMemoryPool();
    return 0;
}
