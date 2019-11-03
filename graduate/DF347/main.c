#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <lib/recordminheap.h>
#include "lib/hashmap.h"
#include "lib/util.h"
#include "lib/io.h"
#include "lib/index.h"
#include "lib/aggregation.h"
/*
/data/ccf_big_data/customer.txt /data/ccf_big_data/orders.txt /data/ccf_big_data/lineitem.txt 1 BUILDING 1995-03-29 1995-03-27 5
/data/ccf_big_data/customer.txt /data/ccf_big_data/orders.txt /data/ccf_big_data/lineitem.txt
 */
#define MaxOrderdate 19980802
#define MinOrderdate 19920101
int main(int argc, char **argv) {
    int CUSTOMER_TABLE_ROW_COUNT = 15 * 1000 * 1000;
    int ORDERS_TABLE_ROW_COUNT = 150 * 1000 * 1000;
    int LINEITEM_TABLE_ROW_COUNT = 600037902;
    InitMemoryPool();
    QueryParam queryParam = ParseQueryParam(argc, argv);
    Customer customer = ReadCustomerTable(queryParam.customerPath, CUSTOMER_TABLE_ROW_COUNT);
    Order orders = CutReadOrderTable(queryParam.ordersPath, ORDERS_TABLE_ROW_COUNT, &queryParam);
    Lineitem lineitem = CutReadLineitemTable(queryParam.lineitemPath, LINEITEM_TABLE_ROW_COUNT, &queryParam);
    CustomerIndex customerIndex = CreateCustomerIndex(&customer, CUSTOMER_TABLE_ROW_COUNT);
    OrderIndex orderIndex = CreateOrderIndex(&orders, orders.Row, CUSTOMER_TABLE_ROW_COUNT);
    LineitemIndex lineitemIndex = CreateLineitemIndex(&lineitem, lineitem.Row, ORDERS_TABLE_ROW_COUNT * 5);
    Record** ret = GetMemory(sizeof(Record*)/sizeof(int) * 1000);
    for (int round = 0; round < queryParam.round; ++round) {
        int mktsegmentCondition = queryParam.mktsegment[round];
        int orderdateCondition = queryParam.orderdate[round];
        int shipdateCondition = queryParam.shipdate[round];
        int topn = queryParam.topn[round];
        PtrList table = NEW_PTR_LIST_NODE;
        for (struct ListNode *i = customerIndex.mktsegment2custkey[mktsegmentCondition - 1]->Next; i; i = i->Next) {
            int custkey = i->Data;
            for (struct ListNode *j = orderIndex.custkey2order[custkey - 1]->Next; j; j = j->Next) {
                int offset = j->Data;
                int orderdate = orders.orderdate[offset];
                if (orderdate >= orderdateCondition) continue;
                int orderkey = orders.orderkey[offset];
                for (struct ListNode *k = lineitemIndex.orderkey2lineitem[orderkey - 1]->Next; k; k = k->Next) {
                    if (lineitem.shipdate[k->Data] <= shipdateCondition) continue;
                    Record *row = (Record *) GetMemory(sizeof(Record) / sizeof(int));
                    row->orderdate = orderdate;
                    row->orderkey = orderkey;
                    row->extendedprice = lineitem.extendedprice[k->Data];
                    InsertPtr(table, row)
                    printf("");
                }
            }
        }
        int dateRange = MaxOrderdate - MinOrderdate + 1;
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
        printf("l_orderkey|o_orderdate|revenue\n");
        int retIndex = topn;
        while (!Record_IsEmpty(H)) {
            Record *record = Record_DeleteMin(H);
            ret[--retIndex] = record;
        }
        for (int i = 0; i < topn; ++i) {
            Record *record = ret[i];
            printf("%d", record->orderkey);
            printf("|");
            PrintDate(record->orderdate);
            printf("|");
            PrintPrice(record->extendedprice);
            printf("\n");
        }
    }
    DisposeMemoryPool();
    return 0;
}