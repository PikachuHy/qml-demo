//
// Created by pikachu on 2019/7/25.
//

#ifndef DATASTRUCTURES_HASHSEP_H
#define DATASTRUCTURES_HASHSEP_H
struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;
typedef int ElementType;
HashTable InitializeTable(int TableSize);
void DestoryTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P);
char* ToString(HashTable H);
#endif //DATASTRUCTURES_HASHSEP_H
