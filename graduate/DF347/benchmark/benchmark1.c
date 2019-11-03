//
// Created by PikachuHy on 2019/10/22.
//

#include "benchmark.h"
#include "io.h"
#include "index.h"
#include "aggregation.h"
#include "hashmap.h"
#include "recordminheap.h"

#include "benchmark.h"
#include "io.h"
#include "index.h"

#include "benchmark.h"
#include "io.h"
#include "index.h"
#include "aggregation.h"
#include "hashmap.h"
#include "recordminheap.h"
#include <stdio.h>
#define MaxOrderdate 19980802
#define MinOrderdate 19920101

PtrList join(Order *orders, Lineitem *lineitem, CustomerIndex *customerIndex, OrderIndex *orderIndex,
             LineitemIndex *lineitemIndex, int mktsegmentCondition, int orderdateCondition, int shipdateCondition);

void outputResult(int topn, Record **ret, struct __RecordMinHeap *H);

RecordMinHeap aggregationQuery(int topn, int dateRange, struct PtrNode *table);

int main(int argc, char **argv) {
    if (argc < 8) {
        printf("ERROR: Must input query param first\n");
        exit(1);
    }
    int CUSTOMER_TABLE_ROW_COUNT = 15 * 1000 * 1000;
    int ORDERS_TABLE_ROW_COUNT = 150 * 1000 * 1000;
//int LINEITEM_TABLE_ROW_COUNT = 600 * 1000 * 1000; // 600,037,902
    int LINEITEM_TABLE_ROW_COUNT = 600037902; // 600,037,902

    InitMemoryPool();
    QueryParam queryParam = ParseQueryParam(argc, argv);
    long totalBegintime = clock();
    long begintime, endtime;
    begintime = clock();
    Customer customer = ReadCustomerTable(queryParam.customerPath, CUSTOMER_TABLE_ROW_COUNT);
    Order orders = CutReadOrderTable(queryParam.ordersPath, ORDERS_TABLE_ROW_COUNT, &queryParam);
    Lineitem lineitem = CutReadLineitemTable(queryParam.lineitemPath, LINEITEM_TABLE_ROW_COUNT, &queryParam);
    endtime = clock();
    printf("read cost: %fs\n", (endtime - begintime) * 1.0 / CLOCKS_PER_SEC);

    begintime = clock();
    CustomerIndex customerIndex = CreateCustomerIndex(&customer, CUSTOMER_TABLE_ROW_COUNT);
    OrderIndex orderIndex = CreateOrderIndex(&orders, orders.Row, CUSTOMER_TABLE_ROW_COUNT);
    LineitemIndex lineitemIndex = CreateLineitemIndex(&lineitem, lineitem.Row, 5 * ORDERS_TABLE_ROW_COUNT);
    endtime = clock();
    printf("index cost: %fs\n", (endtime - begintime) * 1.0 / CLOCKS_PER_SEC);

    int mktsegmentCondition;
    int orderdateCondition;
    int shipdateCondition;
    int topn;
    Record** ret;
    int dateRange = MaxOrderdate - MinOrderdate + 1;
    for (int round = 0; round < queryParam.round; ++round) {
        SaveMemory();
        ret = GetMemory(sizeof(Record*)/sizeof(int) * 1000);
        printf("round: %d\n", round);
        mktsegmentCondition = queryParam.mktsegment[round];
        orderdateCondition = queryParam.orderdate[round];
        shipdateCondition = queryParam.shipdate[round];
        topn = queryParam.topn[round];

        begintime = clock();
        PtrList table = join(&orders, &lineitem,
                             &customerIndex, &orderIndex, &lineitemIndex,
                             mktsegmentCondition, orderdateCondition, shipdateCondition);
        endtime = clock();
        printf("join cost: %fs\n", (endtime - begintime) * 1.0 / CLOCKS_PER_SEC);

        begintime = clock();
        RecordMinHeap H = aggregationQuery(topn, dateRange, table);
        outputResult(topn, ret, H);
        endtime = clock();
        printf("Query cost: %fs\n", (endtime - begintime) * 1.0 / CLOCKS_PER_SEC);
        RestoreMemory();
    }
    DisposeMemoryPool();
    long totalEndtime = clock();

    printf("Total cost: %fs\n", (totalEndtime - totalBegintime) * 1.0 / CLOCKS_PER_SEC);
    return 0;
}

RecordMinHeap aggregationQuery(int topn, int dateRange, struct PtrNode *table) {
    HashMap *orderdate2orderkeyMap = (HashMap *) GetMemory(sizeof(HashMap) / sizeof(int) * dateRange);
    for (int i = 0; i < dateRange; ++i) {
        orderdate2orderkeyMap[i] = CreateHashMap(sizeof(int), 1000);
    }
    struct PtrNode *it = (struct PtrNode *) table->Next;
    while (it) {
        Record *row = (Record *) it->Data;
        HashMap orderKeyMap = orderdate2orderkeyMap[row->orderdate - MinOrderdate];
        int *sum = Get(orderKeyMap, row->orderkey);
        if (sum == NULL) {
            sum = GetMemory(1);
        }
        *sum += row->extendedprice;
        Put(orderKeyMap, row->orderkey, sum);
        it = it->Next;
    }
    RecordMinHeap H = Record_CreateMinHeap(topn);
    for (int i = 0; i < dateRange; ++i) {
        int date = i + MinOrderdate;
        HashMap_Foreach4(orderdate2orderkeyMap[i], &ConstructTopN, &date, H);
    }
    return H;
}

void outputResult(int topn, Record **ret, struct __RecordMinHeap *H) {
    printf("l_orderkey|o_orderdate|revenue\n");
    int retIndex = topn;
    while (!Record_IsEmpty(H)) {
        Record *record = Record_DeleteMin(H);
        ret[--retIndex] = record;
    }
    for (int i = 0; i < topn; ++i) {
        Record *record = ret[i];
        if (record == NULL) continue;
        printf("%d", record->orderkey);
        printf("|");
        PrintDate(record->orderdate);
        printf("|");
        PrintPrice(record->extendedprice);
        printf("\n");
    }
}

PtrList join(Order *orders, Lineitem *lineitem, CustomerIndex *customerIndex, OrderIndex *orderIndex,
             LineitemIndex *lineitemIndex, int mktsegmentCondition, int orderdateCondition, int shipdateCondition) {
    PtrList table = NEW_PTR_LIST_NODE;
    for (struct ListNode *i = (*customerIndex).mktsegment2custkey[mktsegmentCondition - 1]->Next; i; i = i->Next) {
        int custkey = i->Data;
        for (struct ListNode *j = (*orderIndex).custkey2order[custkey - 1]->Next; j; j = j->Next) {
            int offset = j->Data;
            int orderdate = (*orders).orderdate[offset];
            if (orderdate >= orderdateCondition) continue;
            int orderkey = (*orders).orderkey[offset];
            for (struct ListNode *k = (*lineitemIndex).orderkey2lineitem[orderkey - 1]->Next; k; k = k->Next) {
                if ((*lineitem).shipdate[k->Data] <= shipdateCondition) continue;
                Record *row = (Record *) GetMemory(sizeof(Record) / sizeof(int));
                row->orderdate = orderdate;
                row->orderkey = orderkey;
                row->extendedprice = (*lineitem).extendedprice[k->Data];
                InsertPtr(table, row)
            }
        }
    }
    return table;
}
