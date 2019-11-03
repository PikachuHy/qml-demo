//
// Created by PikachuHy on 2019/10/13.
//

#include "io.h"
#include "util.h"
#include "memorypool.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
//#include <zconf.h>
//#define Multiply10(n) ((n<<1) + (n<<3))
#define Multiply10(n) (n * 10)

Customer ReadCustomerTable(const char* path, int rowCount) {
    Customer customer;
    customer.custkey = GetMemory(rowCount);
    customer.mktsegment = GetMemory(rowCount);

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Can't read file: %s\n", path);
        exit(1);
    }
    struct stat sb;
    fstat(fd, &sb);
    void *start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (start == MAP_FAILED) {
        printf("ERROR: Use mmap failed.\n");
        exit(1);
    }
    char *buffer = start;
    for (int i = 0; i < rowCount; ++i) {
        int key = 0;
        while(*buffer != '|') {
            key = Multiply10(key) + *buffer - '0';
            buffer++;
        }
        buffer++;
        customer.custkey[i] = key;
        if (key < 0) {
            printf("ERROR: custkey %d\n", key);
            exit(1);
        }
        switch (*buffer) {
            case 'A': {
                customer.mktsegment[i] = MKT_AUTOMOBILE;
                buffer += 11;
                break;
            }
            case 'B': {
                customer.mktsegment[i] = MKT_BUILDING;
                buffer += 9;
                break;
            }
            case 'F': {
                customer.mktsegment[i] = MKT_FURNITURE;
                buffer += 10;
                break;
            }
            case 'H': {
                customer.mktsegment[i] = MKT_HOUSEHOLD;
                buffer += 10;
                break;
            }
            case 'M': {
                customer.mktsegment[i] = MKT_MACHINERY;
                buffer += 10;
                break;
            }
            default: {
                printf("ERROR: Unknown ");
                while(*buffer!='\n') {
                    printf("%c", *buffer);
                    buffer++;
                }
                printf("\n");
                exit(1);
            }
        }
    }
    munmap(start, sb.st_size);
    close(fd);
    return customer;
}
Order ReadOrderTable(const char* path, int rowCount) {
    Order order;
    order.custkey = GetMemory(rowCount);
    order.orderkey = GetMemory(rowCount);
    order.orderdate = GetMemory(rowCount);
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Can't read file: %s\n", path);
        exit(1);
    }
    struct stat sb;
    fstat(fd, &sb);
    void *start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (start == MAP_FAILED) {
        printf("ERROR: Use mmap failed.\n");
        exit(1);
    }
    char *buffer = start;
    for (int i = 0; i < rowCount; ++i) {

        int key = 0;
        while(*buffer != '|') {
            key = Multiply10(key) + *buffer - '0';
            buffer++;
        }
        buffer++;
        order.orderkey[i] = key;
        key = 0;
        while (*buffer != '|') {
            if(*buffer == '.') {
                buffer++;
                continue;
            }
            key = Multiply10(key) + *buffer - '0';
            buffer++;
        }
        buffer++;
        order.custkey[i] = key;
        int date = 0;
        sdate2idate(date, buffer)
        buffer += 11;
        order.orderdate[i] = date;

    }
    munmap(start, sb.st_size);
    close(fd);
    return order;
}
Lineitem ReadLineitemTable(const char* path, int rowCount) {
    Lineitem lineitem;
    lineitem.orderkey = GetMemory(rowCount);
    lineitem.extendedprice = GetMemory(rowCount);
    lineitem.shipdate = GetMemory(rowCount);
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Can't read file: %s\n", path);
        exit(1);
    }
    struct stat sb;
    fstat(fd, &sb);
    void *start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (start == MAP_FAILED) {
        printf("ERROR: Use mmap failed.\n");
        exit(1);
    }
    char *buffer = start;
    for (int i = 0; i < rowCount; ++i) {
        int key = 0;
        while(*buffer != '|') {
            key = key * 10 + *buffer - '0';
            buffer++;
        }
        buffer++;
        lineitem.orderkey[i] = key;
        if (key < 0) {
            printf("ERROR: orderkey %d\n", key);
            exit(1);
        }
        int price = 0;
        while (*buffer != '|') {
            if(*buffer == '.') {
                buffer++;
                continue;
            }
            price = price * 10 + *buffer - '0';
            buffer++;
        }
        buffer++;
        lineitem.extendedprice[i] = price;
        int date = 0;
        sdate2idate(date, buffer)
        buffer += 11;
        lineitem.shipdate[i] = date;
    }
    munmap(start, sb.st_size);
    close(fd);
    return lineitem;
}

QueryParam ParseQueryParam(int argc, char **argv) {
    QueryParam ret;
    ret.customerPath = argv[1];
    ret.ordersPath = argv[2];
    ret.lineitemPath = argv[3];
    ret.minShipdate = INT_MAX;
    ret.maxOrderdate = INT_MIN;
    char *s;
    s = argv[4];
    ret.round = *s - '0';
    s++;
    while(*s != '\0') {
        ret.round = ret.round * 10 + *s - '0';
        s++;
    }
    ret.mktsegment = GetMemory(ret.round);
    ret.orderdate = GetMemory(ret.round);
    ret.shipdate = GetMemory(ret.round);
    ret.topn = GetMemory(ret.round);
    for (int i = 0; i < ret.round; ++i) {
        // 解析 c_mktsegment
        s = argv[4 + i * 4 + 1];
        switch (*s) {
            case 'A': {
                ret.mktsegment[i] = MKT_AUTOMOBILE;
                break;
            }
            case 'B': {
                ret.mktsegment[i] = MKT_BUILDING;
                break;
            }
            case 'F': {
                ret.mktsegment[i] = MKT_FURNITURE;
                break;
            }
            case 'H': {
                ret.mktsegment[i] = MKT_HOUSEHOLD;
                break;
            }
            case 'M': {
                ret.mktsegment[i] = MKT_MACHINERY;
                break;
            }
            default: {
                printf("ERROR: Unknown ");
                while(*s!='\n') {
                    printf("%c", *s);
                    s++;
                }
                printf("\n");
                exit(1);
            }
        }
        // 解析 o_orderdate
        s = argv[4 + i * 4 + 2];
        int date = 0;
        sdate2idate(date, s)
        ret.orderdate[i] = date;
        if (date > ret.maxOrderdate) ret.maxOrderdate = date;
        // 解析 l_shipdate
        s = argv[4 + i * 4 + 3];
        sdate2idate(date, s);
        ret.shipdate[i] =date;
        if (date < ret.minShipdate) ret.minShipdate = date;
        // 解析 topn
        s = argv[4 + i * 4 + 4];
        int topn = 0;
        topn = *s - '0';
        s++;
        while(*s != '\0') {
            topn = topn * 10 + *s - '0';
            s++;
        }
        ret.topn[i] = topn;
    }
    return ret;
}

Order CutReadOrderTable(const char *path, int rowCount, QueryParam *param) {
    Order order;
    order.custkey = GetMemory(rowCount);
    order.orderkey = GetMemory(rowCount);
    order.orderdate = GetMemory(rowCount);
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Can't read file: %s\n", path);
        exit(1);
    }
    struct stat sb;
    fstat(fd, &sb);
    void *start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (start == MAP_FAILED) {
        printf("ERROR: Use mmap failed.\n");
        exit(1);
    }
    char *buffer = start;
    int Counter = 0;
    for (int i = 0; i < rowCount; ++i) {

        int key = 0;
        while(*buffer != '|') {
            key = Multiply10(key) + *buffer - '0';
            buffer++;
        }
        buffer++;
        order.orderkey[Counter] = key;
        key = 0;
        while (*buffer != '|') {
            if(*buffer == '.') {
                buffer++;
                continue;
            }
            key = Multiply10(key) + *buffer - '0';
            buffer++;
        }
        buffer++;
        order.custkey[Counter] = key;
        int date = 0;
        sdate2idate(date, buffer)
        buffer += 11;
        order.orderdate[Counter] = date;
        if (date < param->maxOrderdate) Counter++;

    }
    order.Row = Counter;
    munmap(start, sb.st_size);
    close(fd);
    return order;
}

Lineitem CutReadLineitemTable(const char *path, int rowCount, QueryParam *param) {
    Lineitem lineitem;
    lineitem.orderkey = GetMemory(rowCount);
    lineitem.extendedprice = GetMemory(rowCount);
    lineitem.shipdate = GetMemory(rowCount);
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        printf("ERROR: Can't read file: %s\n", path);
        exit(1);
    }
    struct stat sb;
    fstat(fd, &sb);
    void *start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (start == MAP_FAILED) {
        printf("ERROR: Use mmap failed.\n");
        exit(1);
    }
    char *buffer = start;
    int Counter = 0;
    for (int i = 0; i < rowCount; ++i) {
        int key = 0;
        while(*buffer != '|') {
            key = key * 10 + *buffer - '0';
            buffer++;
        }
        buffer++;
        lineitem.orderkey[Counter] = key;
        if (key < 0) {
            printf("ERROR: orderkey %d\n", key);
            exit(1);
        }
        int price = 0;
        while (*buffer != '|') {
            if(*buffer == '.') {
                buffer++;
                continue;
            }
            price = price * 10 + *buffer - '0';
            buffer++;
        }
        buffer++;
        lineitem.extendedprice[Counter] = price;
        int date = 0;
        sdate2idate(date, buffer)
        buffer += 11;
        lineitem.shipdate[Counter] = date;
        if (date > param->minShipdate) Counter++;
    }
    lineitem.Row = Counter;
    munmap(start, sb.st_size);
    close(fd);
    return lineitem;
}
