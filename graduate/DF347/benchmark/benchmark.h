//
// Created by PikachuHy on 2019/10/16.
//

#ifndef DF347_BENCHMARK_H
#define DF347_BENCHMARK_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "memorypool.h"
#define BENCHMARK(F) \
{ \
clock_t begintime, endtime; \
begintime = clock();\
F;\
endtime = clock(); \
printf("%s:%d:%fs\n", __FILE__, __LINE__, (endtime - begintime) * 1.0 / CLOCKS_PER_SEC);\
}
#define BASE "/Users/pikachu/src/demo/"
//#define BASE "/home/css518/src/ccf_big_data/"
#define CONCATE_VAR(A, B) A B
char customerTablePath[] = CONCATE_VAR(BASE, "customer.txt");
char ordersTablePath[] = CONCATE_VAR(BASE, "orders.txt");
char lineitemTablePath[] = CONCATE_VAR(BASE, "lineitem.txt");
#endif //DF347_BENCHMARK_H
