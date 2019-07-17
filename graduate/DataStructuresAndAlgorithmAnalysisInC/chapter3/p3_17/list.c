//
// Created by pikachu on 2019/7/17.
//


#include "list.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct Node {
    ElementType Element;
    bool DeleteFlag;
    Position Next;
};
PtrToNode newNode() {
    PtrToNode ret;
    ret = malloc(sizeof(struct Node));
    ret->Element = 0;
    ret->Next = NULL;
    ret->DeleteFlag = false;
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
            old->DeleteFlag = true;
            Debug("Success delete element: %d\n", X);
            return;
        }
        p = Next(p);
    }
    Warning("Fail to delete element: %d\n", X);
}

bool IsEmpty(List L) {
    return L->Next == NULL;
}

char *ToString(List L) {
    char str[1000] = "";
    Position p = First(L);
    while(p!=NULL) {
        if (!p->DeleteFlag) {
            int data = Retrieve(p);
            sprintf(str, "%s->%d", str, data);
        }
        p = Next(p);
    }
    char* ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}

Position FindRecursion(ElementType X, List L) {
    if (L == NULL) {
        Fatal("L is NULL");
        exit(1);
    }
    if (L->Next == NULL){
        Warning("Can't find element: %d\n", X);
        return NULL;
    }
    if (L->Next->Element == X) {
        Debug("Success find element: %d\n", X);
        return L->Next;
    }
    Position ret = FindRecursion(X, L->Next);
    Debug("FindRecursion");
    return ret;
}
/**
 * O(1) Space
 * @param L
 * @return
 */
List Reserve(List L) {
    Position p = First(L);
    if (p == NULL || p->Next == NULL) {
        return L;
    }
    Position pn;
    Position pnn;
    pn = p->Next;
    pnn = pn->Next;
    p->Next = NULL;
    while(pn!=NULL) {
        pn->Next = p;
        p = pn;
        pn = pnn;
        if (pnn!=NULL) {
            pnn = pnn->Next;
        }
    }
    L->Next = p;
    return L;
}

void Append(ElementType X, List L) {
    Position p = Header(L);
    while(p->Next != NULL) {
        p = Next(p);
    }
    PtrToNode node = newNode();
    node->Element = X;
    p->Next = node;
}

Position Find(ElementType X, List L) {
    if (L == NULL) {
        Fatal("L is NULL\n");
        exit(1);
    }
    Position p = Header(L);
    while(p->Next!=NULL) {
        if (Retrieve(p->Next) == X) {
            Position ret = p->Next;
            p->Next = ret->Next;
            ret->Next = L->Next;
            L->Next = ret;
            Debug("Success to find element: %d\n", X);
            return ret;
        }
        p = Next(p);
    }
    Warning("Fail to find element: %d\n", X);
    return NULL;
}