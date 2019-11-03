//
// Created by PikachuHy on 2019/10/14.
//
#include "io.h"
#include "test.h"
#include "memorypool.h"
int main() {
    char ordersTablePath[] = "/Users/pikachu/src/demo/orders.txt";
    int N = 3;
    InitMemoryPool();
    Order order = ReadOrderTable(ordersTablePath, N);
    int orderkey[] = {
            1, 2, 3
    };
    int custkey[] = {
            3689999, 7800163, 12331391
    };
    int orderdate[] = {
            19960102,
            19961201,
            19931014
    };
    for (int i = 0; i < N; ++i) {
        ASSERT_INT_EQUAL(order.orderkey[i], orderkey[i])
        ASSERT_INT_EQUAL(order.custkey[i], custkey[i])
        ASSERT_INT_EQUAL(order.orderdate[i], orderdate[i])
    }
    DisposeMemoryPool();
    return 0;
}