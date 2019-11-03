//
// Created by PikachuHy on 2019/10/22.
//

#include "test.h"
#include "io.h"
// customer.txt orders.txt lineitem.txt 1 BUILDING 1995-03-29 1995-03-27 5
int test1(int argc, char **argv) {
    InitMemoryPool();
    QueryParam queryParam = ParseQueryParam(argc, argv);
    ASSERT_INT_EQUAL(queryParam.round, 1)
    ASSERT_INT_EQUAL(queryParam.mktsegment[0], MKT_BUILDING)
    ASSERT_INT_EQUAL(queryParam.orderdate[0], 19950329)
    ASSERT_INT_EQUAL(queryParam.shipdate[0], 19950327)
    DisposeMemoryPool();
    return 0;
}
/*
customer.txt orders.txt lineitem.txt 3
 BUILDING 1995-03-29 1995-03-27 5
 BUILDING 1995-02-29 1995-04-27 10
 BUILDING 1995-03-28 1995-04-27 2
 */
int main(int argc, char **argv) {
    InitMemoryPool();
    QueryParam queryParam = ParseQueryParam(argc, argv);
    ASSERT_INT_EQUAL(queryParam.round, 3)
    ASSERT_INT_EQUAL(queryParam.mktsegment[0], MKT_BUILDING)
    ASSERT_INT_EQUAL(queryParam.orderdate[0], 19950329)
    ASSERT_INT_EQUAL(queryParam.shipdate[0], 19950327)
    ASSERT_INT_EQUAL(queryParam.topn[0], 5)
    ASSERT_INT_EQUAL(queryParam.mktsegment[1], MKT_BUILDING)
    ASSERT_INT_EQUAL(queryParam.orderdate[1], 19950229)
    ASSERT_INT_EQUAL(queryParam.shipdate[1], 19950427)
    ASSERT_INT_EQUAL(queryParam.topn[1], 10)
    ASSERT_INT_EQUAL(queryParam.mktsegment[2], MKT_BUILDING)
    ASSERT_INT_EQUAL(queryParam.orderdate[2], 19950328)
    ASSERT_INT_EQUAL(queryParam.shipdate[2], 19950427)
    ASSERT_INT_EQUAL(queryParam.topn[2], 2)
    DisposeMemoryPool();

}