//
// Created by PikachuHy on 2019/10/14.
//

#ifndef DF347_INDEX_H
#define DF347_INDEX_H

#include "io.h"
#include "array.h"
#include "list.h"
typedef struct {
    List *mktsegment2custkey;
    int Row;
} CustomerIndex;
typedef struct {
    List *custkey2order;
    int Row;
//    int MaxOrderdate;
//    int MinOrderdate;
} OrderIndex;
typedef struct {
    List *orderkey2lineitem;
    int Row;
} LineitemIndex;

CustomerIndex CreateCustomerIndex(const Customer * customer, int N);
OrderIndex CreateOrderIndex(const Order * order, int N, int custkeyRange);
LineitemIndex CreateLineitemIndex(const Lineitem * lineitem, int N, int orderkeyRange);
#endif //DF347_INDEX_H
