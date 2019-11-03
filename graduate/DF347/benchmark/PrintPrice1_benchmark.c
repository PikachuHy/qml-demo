//
// Created by PikachuHy on 2019/10/22.
//

#include "benchmark.h"
#include "io.h"
void benchmark1() { // 2.60s
    InitMemoryPool();
    int N = 1000 * 1000;
    Lineitem lineitem = ReadLineitemTable(lineitemTablePath, N);
    BENCHMARK(
            for (int i = 0; i < N; ++i) {
                PrintPrice(lineitem.extendedprice[i])
                printf("\n");
            }
            )
    DisposeMemoryPool();
}
int main() {
    benchmark1();
    return 0;
}