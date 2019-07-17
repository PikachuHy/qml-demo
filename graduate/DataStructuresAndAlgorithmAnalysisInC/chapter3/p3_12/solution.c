//
// Created by pikachu on 2019/7/16.
//
#include "solution.h"
#include "list.h"
#include "stack.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
List ReserveByStack(List L) {
    Stack s = CreateStack();
    while(!IsEmpty(L)) {
        Position p = First(L);
        int data = Retrieve(p);
        Push(data, s);
        Delete(data, L);
    }
    Position p = L;
    while(!IsEmptyStack(s)) {
        int data = Top(s);
        Insert(data, L, p);
        p = Next(p);
        Pop(s);
    }
    return L;
}