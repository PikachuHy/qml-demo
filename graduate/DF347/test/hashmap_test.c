//
// Created by PikachuHy on 2019/10/17.
//

#include "test.h"
#include "hashmap.h"
#include "memorypool.h"

void test1() {
    InitMemoryPool();
    HashMap hashMap = CreateHashMap(sizeof(int), 1000);
    int *value = Get(hashMap, 100);
    ASSERT_INT_EQUAL(value, 0)
    value = GetMemory(1);
    *value = 1024;
    Put(hashMap, 100, value);
    int *value2 = Get(hashMap, 100);
    ASSERT_FALSE(value2 == 0)
    ASSERT_INT_EQUAL(*value2, 1024)
    int *value3 = GetMemory(1);
    *value3 = 10086;
    Put(hashMap, 100, value3);
    int *value4 = Get(hashMap, 100);
    ASSERT_FALSE(value4 == 0)
    ASSERT_INT_EQUAL(*value4, 10086)
    DisposeMemoryPool();
}

int main() {
    test1();
    return 0;
}