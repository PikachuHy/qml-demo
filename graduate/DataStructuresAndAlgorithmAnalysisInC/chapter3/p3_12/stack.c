//
// Created by pikachu on 2019/7/16.
//

#include "stack.h"
#include "debug.h"
#include <stdlib.h>
struct Node {
    ElementType Element;
    PtrToNode Next;
};
bool IsEmptyStack(Stack S) {
    return S->Next == NULL;
}
PtrToNode newStackNode() {
    PtrToNode ret;
    ret = malloc(sizeof(struct Node));
    ret->Element = 0;
    ret->Next = NULL;
    return ret;
}
Stack CreateStack() {
    Stack ret;
    ret = newStackNode();
    return ret;
}
void Push(ElementType X, Stack S) {
    PtrToNode t;
    t = newStackNode();
    t->Element = X;
    t->Next = S->Next;
    S->Next = t;
}
void Pop(Stack S) {
    if(IsEmptyStack(S)) {
        Warning("S is empty\n");
        return;
    }
    PtrToNode old = S->Next;
    S->Next = old->Next;
    free(old);
}
ElementType Top(Stack S) {
    if (IsEmptyStack(S)) {
        Fatal("S is empty\n");
        exit(1);
    }
    return S->Next->Element;
}