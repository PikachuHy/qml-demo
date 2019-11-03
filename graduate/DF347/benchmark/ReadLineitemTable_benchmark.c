//
// Created by PikachuHy on 2019/10/13.
//

#include "benchmark.h"
#include "io.h"
#include "memorypool.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * 测试结果
 * 2019年10月13日 0.3 3.1 31 无 无 超过int范围
 * 2019年10月14日 0.06 0.69 8.15 无 无 超过int范围
 */
// 最大60亿
#define TEST(N) \
InitMemoryPool();\
int rowCount = N; \
BENCHMARK(\
Lineitem lineitem = ReadLineitemTable(lineitemTablePath, rowCount); \
)\
DisposeMemoryPool();

void benchmark1() {
    TEST(1000 * 1000)
}

void benchmark2() {
    TEST(10 * 1000 * 1000)
}

void benchmark3() {
    TEST(100 * 1000 * 1000)
}

void benchmark4() {
    TEST(600037902)
}
/*
void benchmark5() {
    TEST(6 * 1000 * 1000 * 1000)
}*/

int main() {
    benchmark1();
    benchmark2();
    benchmark3();
    benchmark4();
//    benchmark5();
    return 0;
}