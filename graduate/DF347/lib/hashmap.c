//
// Created by PikachuHy on 2019/10/17.
//

#include "hashmap.h"
#include "memorypool.h"
#include <stdlib.h>
#include <stdio.h>
struct HashEntry {
    int hash;
    int key;
    void* value;
    struct HashEntry *next;
};
#define NEW_HASH_ENTRY ((struct HashEntry*)GetMemory(sizeof(struct HashEntry)/sizeof(int)))
struct __HashMap {
    int size;
    int capacity;
    int valueTypeLength;
    struct HashEntry **list;
};

HashMap CreateHashMap(int len, int InitializeCapacity) {
    if (InitializeCapacity < 8) {
        InitializeCapacity = 8;
    }
    HashMap ret = GetMemory(sizeof(struct __HashMap) / sizeof(int));
    ret->size = 0;
    ret->capacity = InitializeCapacity;
    ret->valueTypeLength = len;
    // rehash需要释放内存，所以不能用自己写的内存池
    ret->list = malloc(sizeof(struct HashEntry*) * ret->capacity);
    for (int i = 0; i < ret->capacity; ++i) {
        ret->list[i] = NEW_HASH_ENTRY;
    }
    return ret;
}

void Put(HashMap hashMap, int key, void *value) {
    int hash = key;
    int index = key % hashMap->capacity;
    struct HashEntry *it = hashMap->list[index];
    while(it->next) {
        it = it->next;
        if (it->hash == hash && it->key == key) {
            it->value = value;
            return;
        }
    }
    it->next = NEW_HASH_ENTRY;
    it = it->next;
    it->hash = hash;
    it->key = key;
    it->value = value;
}

void* Get(HashMap hashMap, int key) {
    int hash = key;
    int index = key % hashMap->capacity;
    struct HashEntry *it = hashMap->list[index];
    while (it->next) {
        it = it->next;
        if (it->hash == hash && it->key == key) {
            return it->value;
        }
    }
    return 0;
}

void DisposeHashMap(HashMap hashMap) {
    free(hashMap->list);
}

void HashMap_Foreach(HashMap hashMap, void (*visit)(void *)) {
    for (int i = 0; i < hashMap->capacity; ++i) {
        struct HashEntry * it = hashMap->list[i]->next;
        while(it) {
            visit(it->value);
            it = it->next;
        }
    }
}

void HashMap_Foreach2(HashMap hashMap, void (*visit)(void *, void *), void *param2) {
    for (int i = 0; i < hashMap->capacity; ++i) {
        struct HashEntry * it = hashMap->list[i]->next;
        while(it) {
            visit(it->value, param2);
            it = it->next;
        }
    }

}

void HashMap_Foreach3(HashMap hashMap, void (*visit)(void *, void *, void *), void *param3) {
    for (int i = 0; i < hashMap->capacity; ++i) {
        struct HashEntry * it = hashMap->list[i]->next;
        while(it) {
            visit(&it->key, it->value, param3);
            it = it->next;
        }
    }

}

void HashMap_Foreach4(HashMap hashMap, void (*visit)(void *, void *, void *, void *), void *param3, void *param4) {
    for (int i = 0; i < hashMap->capacity; ++i) {
        struct HashEntry * it = hashMap->list[i]->next;
        while(it) {
            visit(&it->key, it->value, param3,param4);
            it = it->next;
        }
    }
}

