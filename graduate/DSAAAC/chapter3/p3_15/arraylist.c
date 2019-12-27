//
// Created by pikachu on 2019/7/17.
//

#include "arraylist.h"
#include "debug.h"
#include <stdlib.h>
#include <string.h>
struct ArrayListHead {
    ElementType *Data;
    int Len;
    int Capability;
};
ArrayList MakeArrayList() {
    ArrayList ret;
    ret = malloc(sizeof(struct ArrayListHead));
    ret->Len = 0;
    ret->Capability = 10;
    ret->Data = malloc(sizeof(ElementType) * ret->Capability);
    return ret;
}
void ArrayList_EnsureCapability(ArrayList L) {
    if (L->Capability == L->Len) {
        L->Capability *= 2;
        ElementType *arr;
        arr = malloc(sizeof(ElementType) * L->Capability);
        for (int i = 0; i < L->Len; ++i) {
            arr[i] = L->Data[i];
        }
        free(L->Data);
        L->Data = arr;
    }
}
void ArrayList_Append(ElementType X, ArrayList L) {
    ArrayList_EnsureCapability(L);
    L->Data[L->Len++] = X;
}
void ArrayList_Find(ElementType X, ArrayList L) {
    int index = -1;
    for (int i = 0; i < L->Len; ++i) {
        if(L->Data[i] == X) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        Warning("Fail to find element: %d\n", X);
        return;
    }
    for (int i = index; i > 0; --i) {
        L->Data[i] = L->Data[i-1];
    }
    L->Data[0] = X;
}
char* ArrayList_ToString(ArrayList L) {
    char str[1000] = "";
    for (int i = 0; i < L->Len; ++i) {
        sprintf(str, "%s->%d", str,L->Data[i]);
    }
    char *ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}