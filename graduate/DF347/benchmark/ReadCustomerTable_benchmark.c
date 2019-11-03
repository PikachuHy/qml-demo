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
 * 2019年10月13日 0.2
 * 2019年10月14日 0.054
 */
// 最大1500万
void benchmark1() {
    InitMemoryPool();
    int rowCount = 1500 * 1000;
    BENCHMARK(
    Customer customer = ReadCustomerTable(customerTablePath, rowCount);
    )
    DisposeMemoryPool();
}
void benchmark2() {
    InitMemoryPool();
    int rowCount = 15 * 1000 * 1000;
    BENCHMARK(
            Customer customer = ReadCustomerTable(customerTablePath, rowCount);
            )
    DisposeMemoryPool();
}

int main() {
//    benchmark1();
    benchmark2();
    return 0;
}
