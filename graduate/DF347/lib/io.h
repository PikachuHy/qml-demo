//
// Created by PikachuHy on 2019/10/13.
//

#ifndef DF347_IO_H
#define DF347_IO_H
#define MKT_AUTOMOBILE 1
#define MKT_BUILDING 2
#define MKT_FURNITURE 3
#define MKT_HOUSEHOLD 4
#define MKT_MACHINERY 5
typedef struct {
    int *custkey;
    int *mktsegment;
} Customer;
typedef struct {
    int *orderkey;
    int *custkey;
    int *orderdate;
    int Row;
} Order;
typedef struct {
    int *orderkey;
    int *extendedprice;
    int *shipdate;
    int Row;
} Lineitem;
typedef struct {
    char *customerPath;
    char *ordersPath;
    char *lineitemPath;
    int round;
    int *mktsegment;
    int *orderdate;
    int *shipdate;
    int *topn;
    int maxOrderdate;
    int minShipdate;
} QueryParam;
QueryParam ParseQueryParam(int argc, char** argv);
Customer ReadCustomerTable(const char* path, int rowCount);
Order ReadOrderTable(const char* path, int rowCount);
Lineitem ReadLineitemTable(const char* path, int rowCount);
// 读原始数据集时同时过滤
Order CutReadOrderTable(const char* path, int rowCount, QueryParam *param);
Lineitem CutReadLineitemTable(const char* path, int rowCount, QueryParam *param);

#define PrintDate(idate) \
{ \
    int __date = idate; \
    int __Y = __date / 10000;\
    __date %= 10000; \
    int __M = __date / 100; \
    int __D = __date % 100; \
    printf("%d", __Y);\
    printf("-");\
    if (__M < 10) printf("0"); \
    printf("%d", __M); \
    printf("-"); \
    if (__D < 10) printf("0"); \
    printf("%d", __D); \
}
#define PrintPrice(iprice) \
{\
  printf("%.2f", 1.0 * iprice/100);\
}
#endif //DF347_IO_H
