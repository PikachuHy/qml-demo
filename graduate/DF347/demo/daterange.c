//
// Created by PikachuHy on 2019/10/14.
//
#include "io.h"
#include "memorypool.h"
#include <stdio.h>
#include <limits.h>
int main() {
    InitMemoryPool();
    char ordersTablePath[] = "/data/ccf_big_data/orders.txt";
    char lineitemTablePath[] = "/data/ccf_big_data/lineitem.txt";
    int CUSTOMER_TABLE_ROW_COUNT = 15 * 1000 * 1000;
    int ORDERS_TABLE_ROW_COUNT = 150 * 1000 * 1000;
//int LINEITEM_TABLE_ROW_COUNT = 600 * 1000 * 1000; // 600,037,902
    int LINEITEM_TABLE_ROW_COUNT = 600037902; // 600,037,902
    Order order = ReadOrderTable(ordersTablePath, ORDERS_TABLE_ROW_COUNT);
    int maxDate = INT_MIN;
    int minDate = INT_MAX;
    for (int i = 0; i < ORDERS_TABLE_ROW_COUNT; ++i) {
        int date = order.orderdate[i];
        if (date > maxDate) maxDate = date;
        if (date < minDate) minDate = date;
    }
    printf("order date range: [%d, %d]\n", minDate, maxDate);
    Lineitem lineitem = ReadLineitemTable(lineitemTablePath, LINEITEM_TABLE_ROW_COUNT);

    maxDate = INT_MIN;
    minDate = INT_MAX;
    for (int i = 0; i < ORDERS_TABLE_ROW_COUNT; ++i) {
        int date = lineitem.shipdate[i];
        if (date > maxDate) maxDate = date;
        if (date < minDate) minDate = date;
    }
    printf("ship date range: [%d, %d]\n", minDate, maxDate);
    DisposeMemoryPool();
    printf("Done!\n");
    return 0;
}
/*
order date range: [19920101, 19980802]
ship date range: [19920102, 19981201]
 */