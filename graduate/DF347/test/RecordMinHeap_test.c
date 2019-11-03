//
// Created by PikachuHy on 2019/10/22.
//

#include <stdlib.h>
#include "test.h"
#include "time.h"
#include "recordminheap.h"
static void shuttle(int *A, int N) {
    for(int i=N-1;i>=0;i--) {
        int j = rand() % (i+1);
        int t = A[i];
        A[i] = A[j];
        A[j] = t;
    }
}
Record * record(int X) {
    Record *ret = GetMemory(sizeof(Record)/sizeof(int));
    ret->extendedprice = X;
    return ret;
}
void test1() {
    InitMemoryPool();
    int N = 10;
    int M = 5;
    int *A = GetMemory(N);
    for (int i = 0; i < N; ++i) {
        A[i] = i;
    }
    shuttle(A, N);
    RecordMinHeap H = Record_CreateMinHeap(M);
    for (int i = 0; i < N; ++i) {
        Record_Insert(H, record(A[i]));
    }
    int expected[] = {
            5,6,7,8,9
    };
    for (int i = 0; i < M; ++i) {
        Record* r = Record_DeleteMin(H);
        ASSERT_INT_EQUAL(r->extendedprice, expected[i]);
    }
    DisposeMemoryPool();
}
void test2() {
    InitMemoryPool();
    int N = 100;
    int M = 10;
    int *A = GetMemory(N);
    for (int i = 0; i < N; ++i) {
        A[i] = i;
    }
    shuttle(A, N);
    RecordMinHeap H = Record_CreateMinHeap(M);
    for (int i = 0; i < N; ++i) {
        Record_Insert(H, record(A[i]));
    }
    int expected[M];
    for (int i = 0; i < M; ++i) {
        expected[i] = N - M + i;
    }
    for (int i = 0; i < M; ++i) {
        Record* r = Record_DeleteMin(H);
        ASSERT_INT_EQUAL(r->extendedprice, expected[i]);
    }
    DisposeMemoryPool();
}
int main() {
    srand(time(NULL));
    test1();
    test2();
    return 0;
}