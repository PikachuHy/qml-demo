//
// Created by PikachuHy on 2019/10/22.
//

#include "benchmark.h"
#include "io.h"
#include "memorypool.h"
void benchmark1() { // 1.85s
    InitMemoryPool();
    int N = 1000 * 1000;
    Order orders = ReadOrderTable(ordersTablePath, N);
    BENCHMARK(
    for (int i = 0; i < N; ++i) {
        PrintDate(orders.orderdate[i])
        printf("\n");
    }
    )
    DisposeMemoryPool();
}
int main() {
    benchmark1();
    return 0;
}