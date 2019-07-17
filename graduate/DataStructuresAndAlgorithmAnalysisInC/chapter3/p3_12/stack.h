//
// Created by pikachu on 2019/7/16.
//

#ifndef DATASTRUCTURES_STACK_H
#define DATASTRUCTURES_STACK_H

#include <stdbool.h>
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
typedef int ElementType;
bool IsEmptyStack(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmptyStack(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
#endif //DATASTRUCTURES_STACK_H
