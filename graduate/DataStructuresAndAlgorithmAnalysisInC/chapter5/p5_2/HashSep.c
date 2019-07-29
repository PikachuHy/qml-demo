//
// Created by pikachu on 2019/7/25.
//

#include "HashSep.h"
#include "debug.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MinTableSize 3
struct ListNode {
    ElementType Element;
    Position Next;
};
typedef Position List;

struct HashTbl {
    int TableSize;
    List *TheList;
};
int Hash(int key, int size) {
    return key % size;
}
bool IsPrime(int n) {
    if (n == 2 || n == 3) {
        return true;
    }
    for (int i = 2; i < n / 2 + 1; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int NextPrime(int n) {
    while (true) {
        if (IsPrime(n)) {
            return n;
        }
        n++;
    }
}

HashTable InitializeTable(int TableSize) {
    HashTable H;
    if (TableSize < MinTableSize) {
        Error("Table size too small\n");
        return NULL;
    }
    H = malloc(sizeof(struct HashTbl));
    if (H == NULL) {
        Fatal("Out of Space\n");
        exit(1);
    }
    H->TableSize = NextPrime(TableSize);
    H->TheList = malloc(sizeof(List) * H->TableSize);
    if (H->TheList == NULL) {
        Fatal("Out of space!!!\n");
        exit(1);
    }
    for (int i = 0; i < H->TableSize; ++i) {
        H->TheList[i] = malloc(sizeof(struct ListNode));
        if (H->TheList[i] == NULL) {
            Fatal("Out of space!!!\n");
            exit(1);
        }
        H->TheList[i]->Next = NULL;
    }

    return H;
}

void DestoryTable(HashTable H) {
    if (H == NULL) {
        Warning("HashTable is NULL\n");
        return;
    }
    if (H->TheList == NULL) {
        Warning("HashTable TheList is NULL\n");
        return;
    }
    free(H->TheList);
    free(H);
    H = NULL;
}

Position Find(ElementType Key, HashTable H) {
    Position P;
    List L;
    L = H->TheList[Hash(Key, H->TableSize)];
    P = L->Next;
    while(P!=NULL && P->Element != Key) {
        P = P->Next;
    }
    return P;
}

void Insert(ElementType Key, HashTable H) {
    Position Pos, NewCell;
    List L;
    Pos = Find(Key, H);
    if (Pos == NULL) {
        NewCell = malloc(sizeof(struct ListNode));
        if (NewCell == NULL) {
            Fatal("Out of space!!!\n");
            exit(1);
        }
        L = H->TheList[Hash(Key, H->TableSize)];
        NewCell->Next = L->Next;
        NewCell->Element = Key;
        L->Next = NewCell;
    }
}

char *ToString(HashTable H) {
    Position tmpCell;
    if (H == NULL) {
        Fatal("H is NULL\n");
        exit(1);
    }
    char str[1000] = "";
    for (int i = 0; i < H->TableSize; ++i) {
        tmpCell = H->TheList[i]->Next;
        if (tmpCell == NULL) {
            sprintf(str,"%s->[]", str);
        } else {
            sprintf(str, "%s->[", str);
            while(tmpCell!=NULL) {
                ElementType data = Retrieve(tmpCell);
                sprintf(str, "%s->%d", str, data);
                tmpCell = tmpCell->Next;
            }
            sprintf(str, "%s]", str);
        }
    }
    char *ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}

ElementType Retrieve(Position P) {
    return P->Element;
}


