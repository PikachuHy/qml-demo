//
// Created by PikachuHy on 2019/10/14.
//

#include "index.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

CustomerIndex CreateCustomerIndex(const Customer *customer, int N) {
    CustomerIndex ret;
    ret.Row = 5;
    ret.mktsegment2custkey = GetMemory(sizeof(List)/sizeof(int) * 5);
    for (int i = 0; i < 5; ++i) {
        ret.mktsegment2custkey[i] = NEW_LIST_NODE;
    }
    for (int i = 0; i < N; ++i) {
        int index = customer->mktsegment[i] - 1;
        int custkey = customer->custkey[i];
        if (custkey < 0) {
            printf("Error: custkey %d\n", custkey);
            exit(1);
        }
        InsertData(ret.mktsegment2custkey[index], custkey)
    }
    return ret;
}

OrderIndex CreateOrderIndex(const Order *order, int N, int custkeyRange) {
    OrderIndex ret;
    ret.Row = custkeyRange;
//    ret.MaxOrderdate = INT_MIN;
//    ret.MinOrderdate = INT_MAX;
    ret.custkey2order = (List *) GetMemory(sizeof(List)/sizeof(int) * custkeyRange);
    for (int i = 0; i < ret.Row; ++i) {
        ret.custkey2order[i] = NEW_LIST_NODE;
    }
    for (int i = 0; i < N; ++i) {
        int custkey = order->custkey[i];
        if (custkey < 0) {
            printf("Error: custkey %d\n", custkey);
            exit(1);
        }
        int index = custkey - 1;
        InsertData(ret.custkey2order[index], i)
        // 加了这几条 慢太多了
//        int orderdate = order->orderdate[i];
//        if (orderdate > ret.MaxOrderdate) ret.MaxOrderdate = orderdate;
//        if (orderdate < ret.MinOrderdate) ret.MinOrderdate = orderdate;
    }
    return ret;
}

LineitemIndex CreateLineitemIndex(const Lineitem *lineitem, int N, int orderkeyRange) {
    LineitemIndex ret;
    ret.Row = orderkeyRange;
    ret.orderkey2lineitem = GetMemory(sizeof(List)/ sizeof(int) * orderkeyRange);
    for (int i = 0; i < orderkeyRange; ++i) {
        ret.orderkey2lineitem[i] = NEW_LIST_NODE;
    }
    for (int i = 0; i < N; ++i) {
        int orderkey = lineitem->orderkey[i];
        if (orderkey < 0) {
            printf("Error: orderkey %d; index: %d\n", orderkey, i);
            exit(1);
        }
        int index = orderkey - 1;
        InsertData(ret.orderkey2lineitem[index], i)
    }
    return ret;
}
