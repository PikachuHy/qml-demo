//
// Created by PikachuHy on 2019/10/14.
//

#include "io.h"
#include "test.h"
#include "memorypool.h"
int main() {
    char customerTablePath[] = "/Users/pikachu/src/demo/customer.txt";
    int N = 4;
    InitMemoryPool();
    Customer customer = ReadCustomerTable(customerTablePath, N);
    int custkey[] = {
            1, 2, 3, 4
    };
    int mktsegment[] = {
            2,1,1,5,4
    };
    for (int i = 0; i < N; ++i) {
        ASSERT_INT_EQUAL(customer.custkey[i], custkey[i])
        ASSERT_INT_EQUAL(customer.mktsegment[i], mktsegment[i])
    }
    DisposeMemoryPool();
    return 0;
}