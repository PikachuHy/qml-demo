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
 * 2019年10月13日 0.4 4.0 41
 * 2019年10月14日 0.08 0.9 10
 */
// 最大1.5亿
#define TEST(N) \
InitMemoryPool(); \
int rowCount = N; \
BENCHMARK(\
Order order = ReadOrderTable(ordersTablePath, rowCount); \
)\
DisposeMemoryPool();

void benchmark1() {
    TEST(1500 * 1000)
}

void benchmark2() {
    TEST(15000 * 1000)
}
void benchmark3() {
    TEST(150 * 1000 * 1000)
}
void benchmark4() {
    TEST(1500)
}
int main() {
//    benchmark1();
//    benchmark2();
    benchmark3();
//benchmark4();
    return 0;
}
