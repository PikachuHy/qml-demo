//
// Created by pikachu on 2019/7/16.
//

#ifndef DATASTRUCTURES_LIST_H
#define DATASTRUCTURES_LIST_H
#include <stdbool.h>
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
List MakeEmpty(List L);
bool IsEmpty(List L);
bool IsLast(List L);
Position Find(ElementType X, List L);
Position FindRecursion(ElementType X, List L);
void Delete(ElementType X, List L);
Position FindPrious(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);
Position Next(Position P);
char* ToString(List L);
List Reserve(List L);
#endif //DATASTRUCTURES_LIST_H
