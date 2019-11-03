//
// Created by PikachuHy on 2019/10/18.
//

#ifndef DF347_AGGREGATION_H
#define DF347_AGGREGATION_H
typedef struct {
    int orderkey;
    int orderdate;
    int extendedprice;
} Record;

void ConstructTopN(void *orderkey, void *extendedprice, void *orderdate, void *hashmap);
#endif //DF347_AGGREGATION_H
