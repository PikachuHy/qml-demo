//
// Created by PikachuHy on 2019/10/17.
//
#include "test.h"
#include "index.h"
#include "memorypool.h"
int main() {
    InitMemoryPool();
    char customerTablePath[] = "/Users/pikachu/src/demo/customer.txt";
    int N = 4;
    Customer customer = ReadCustomerTable(customerTablePath, N);
    CustomerIndex customerIndex = CreateCustomerIndex(&customer, 4);
    ASSERT_FALSE(customerIndex.mktsegment2custkey[MKT_BUILDING-1]->Next == NULL)
    ASSERT_INT_EQUAL(customerIndex.mktsegment2custkey[MKT_BUILDING-1]->Next->Data, 1)
    DisposeMemoryPool();
    return 0;
}