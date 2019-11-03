//
// Created by PikachuHy on 2019/10/16.
//

#include "memorypool.h"
#include "log.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static int *memory;
static int *next;
static int *__next;
static size_t total;
static size_t save;
static const int CUSTOMER_TABLE_SIZE = 15 * 1000 * 1000;
static const int ORDER_TABLE_SIZE = 300 * 1000 * 1000;
static const int LINEITEM_TABLE_SIZE = 250 * 1000 * 1000;
static const size_t DEFAULT_MEMORY_POOL_SIZE = 30 * 1000 * 1000l * 1000;
//        CUSTOMER_TABLE_SIZE * 4 +
//        ORDER_TABLE_SIZE * 4 +
//        LINEITEM_TABLE_SIZE * 3;

void InitMemoryPool() {
    memory = calloc(sizeof(int), DEFAULT_MEMORY_POOL_SIZE);
    if (memory == NULL) {
        ERROR("Can't allocate memory; %zu", DEFAULT_MEMORY_POOL_SIZE);
        exit(1);
    }
    next = memory;
    total = 0;
}

void *GetMemory(int len) {
    if (memory == NULL) {
        printf("ERROR: Must init memory pool first\n");
        exit(1);
    }
    if (total + len > DEFAULT_MEMORY_POOL_SIZE) {
        printf("ERROR: Out of memory\n");
        exit(1);
    }
    int *ret = next;
    next += len;
    total += len;
    return ret;
}

void DisposeMemoryPool() {
    free(memory);
}

void SaveMemory() {
    save = total;
    __next = next;
    DEBUG("save: %lu", save);
}

void RestoreMemory() {
    size_t len = total - save + 1;
    total = save;
    DEBUG("total: %lu", total);
    next = __next;
    memset(next, 0, len  * sizeof(int));
}
