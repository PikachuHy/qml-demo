//
// Created by pikachu on 2019/7/16.
//

#include "list.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct Node {
    ElementType Element;
    Position Next;
};
PtrToNode newNode() {
    PtrToNode ret;
    ret = malloc(sizeof(struct Node));
    ret->Element = 0;
    ret->Next = ret;
    return ret;
}
List MakeEmpty(List L) {
    if (L != NULL) {
        DeleteList(L);
    }
    return newNode();
}
Position Header(List L) {
    return L;
}
Position First(List L) {
    return L->Next;
}
void DeleteList(List L) {
    if (L == NULL) {
        Warning("L is NULL");
        return;
    }
    Position p = L;
    while(p!=NULL) {
        Position t = p;
        p = p->Next;
        free(t);
    }
}
Position Next(Position P) {
    return P->Next;
}
void Insert(ElementType X, List L, Position P) {
    if (L == NULL) {
        Fatal("L is NULL");
        exit(1);
    }
    Position p = P;
    if (p == NULL) {
        p = L;
        if (p->Next == NULL) {
            p->Next = L;
        }
    }
    PtrToNode t;
    t = newNode();
    t->Element = X;
    t->Next = p->Next;
    p->Next = t;
}

ElementType Retrieve(Position P) {
    if (P == NULL) {
        Fatal("P is NULL");
        exit(1);
    }
    return P->Element;
}

void Delete(ElementType X, List L) {
    if (L == NULL) {
        Fatal("L is NULL");
        exit(1);
    }
    Position p = Header(L);
    while(p->Next!=NULL && p->Next!=L) {
        if (Retrieve(p->Next) == X) {
            Position old = p->Next;
            p->Next = old->Next;
            free(old);
            Debug("Success delete element: %d\n", X);
            return;
        }
        p = Next(p);
    }
    Warning("Fail to delete element: %d\n", X);
}

bool IsEmpty(List L) {
    return L->Next == L;
}

char *ToString(List L) {
    char str[1000] = "";
    Position p = First(L);
    while(p!=NULL && p != L) {
        int data = Retrieve(p);
        sprintf(str, "%s->%d", str, data);
        p = Next(p);
    }
    char* ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}
