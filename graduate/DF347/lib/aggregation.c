//
// Created by PikachuHy on 2019/10/18.
//

#include "aggregation.h"
#include "hashmap.h"
#include "recordminheap.h"
#include "memorypool.h"
void ConstructTopN(void *orderkey, void *extendedprice, void *orderdate, void *H) {
    Record* record = GetMemory(sizeof(Record)/ sizeof(int));
    record->orderdate = *(int*)orderdate;
    record->orderkey = *(int*)orderkey;
    record->extendedprice = *(int*)extendedprice;
    RecordMinHeap _H = H;
    Record_Insert(_H, record);
}
