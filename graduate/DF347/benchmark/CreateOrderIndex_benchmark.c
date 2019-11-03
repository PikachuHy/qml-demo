//
// Created by PikachuHy on 2019/10/16.
//

#include "benchmark.h"
#include "io.h"
#include "index.h"
int MAX_CUSTKEY_RANGE = 15 * 1000 * 1000;
#define TEST(N) \
InitMemoryPool(); \
int rowCount = N; \
Order order = ReadOrderTable(ordersTablePath, rowCount); \
OrderIndex orderIndex; \
BENCHMARK( \
        orderIndex = CreateOrderIndex(&order, rowCount, MAX_CUSTKEY_RANGE); \
) \
DisposeMemoryPool();

void benchmark1() {
    InitMemoryPool();
    int rowCount = 1000 * 1000;
    Order order = ReadOrderTable(ordersTablePath, rowCount);
    OrderIndex orderIndex;
    BENCHMARK(
     orderIndex = CreateOrderIndex(&order, rowCount, MAX_CUSTKEY_RANGE);
    )
    DisposeMemoryPool();
}

void benchmark2() {
    TEST(10 * 1000 * 1000)
}
void benchmark3() {
    TEST(100 * 1000 * 1000)
}
void benchmark4() {
    TEST(150 * 1000 * 1000)
}
int main() {
    benchmark1();
    benchmark2();
    benchmark3();
    benchmark4();
    return 0;
}