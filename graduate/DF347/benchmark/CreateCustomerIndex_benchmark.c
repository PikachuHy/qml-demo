//
// Created by PikachuHy on 2019/10/16.
//
#include "benchmark.h"
#include "io.h"
#include "index.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
void benchmark1() {
    InitMemoryPool();
    int rowCount = 15 * 1000 * 1000;
    Customer customer = ReadCustomerTable(customerTablePath, rowCount);
    BENCHMARK(
            CustomerIndex customerIndex = CreateCustomerIndex(&customer, rowCount);
            )
    DisposeMemoryPool();
}
int main() {
    benchmark1();
    return 0;
}