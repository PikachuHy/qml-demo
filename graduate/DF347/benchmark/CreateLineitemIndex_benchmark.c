//
// Created by PikachuHy on 2019/10/16.
//
#include "benchmark.h"
#include "index.h"

#define TEST(N) \
InitMemoryPool(); \
int rowCount = N; \
Lineitem lineitem = ReadLineitemTable(lineitemTablePath, rowCount); \
LineitemIndex lineitemIndex; \
BENCHMARK( \
        lineitemIndex = CreateLineitemIndex(&lineitem, rowCount, rowCount * 5);\
)\
DisposeMemoryPool();

void benchmark1() {
    int rowCount = 1000 * 1000;
    InitMemoryPool();
    Lineitem lineitem = ReadLineitemTable(lineitemTablePath, rowCount);
    LineitemIndex lineitemIndex;
    BENCHMARK(
    lineitemIndex = CreateLineitemIndex(&lineitem, rowCount, rowCount * 5);
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
    TEST(50 * 1000 * 1000)
}
void benchmark5() {
    TEST(80 * 1000 * 1000)
}
void benchmark6() {
    TEST(100 * 1000 * 1000)
}
int main() {
    benchmark1();
    benchmark2();
//    benchmark3();
//    benchmark4();
//    benchmark5();
    benchmark6();
    return 0;
}