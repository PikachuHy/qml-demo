//
// Created by pikachu on 2019/7/17.
//

#ifndef DATASTRUCTURES_ARRAYLIST_H
#define DATASTRUCTURES_ARRAYLIST_H
struct ArrayListHead;
typedef struct ArrayListHead* ArrayList;
typedef int ElementType;
ArrayList MakeArrayList();
void ArrayList_Append(ElementType X, ArrayList L);
void ArrayList_Find(ElementType X, ArrayList L);
char* ArrayList_ToString(ArrayList L);
#endif //DATASTRUCTURES_ARRAYLIST_H
