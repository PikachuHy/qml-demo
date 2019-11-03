//
// Created by PikachuHy on 2019/10/16.
//

#ifndef DF347_MEMORYPOOL_H
#define DF347_MEMORYPOOL_H

#include <stdlib.h>
void InitMemoryPool();
void *GetMemory(int len);
void DisposeMemoryPool();
void SaveMemory();
void RestoreMemory();
//#define InitMemoryPool(...)
//#define GetMemory(len) malloc(len * sizeof(int))
//#define DisposeMemoryPool(...)
#endif //DF347_MEMORYPOOL_H
