//
// Created by PikachuHy on 2019/10/17.
//

#ifndef DF347_HASHMAP_H
#define DF347_HASHMAP_H
typedef struct __HashMap * HashMap;

HashMap CreateHashMap(int len, int InitializeCapacity);
void Put(HashMap hashMap, int key, void* value);
void* Get(HashMap hashMap, int key);
void DisposeHashMap(HashMap hashMap);
void HashMap_Foreach(HashMap hashMap, void (*visit)(void*));
void HashMap_Foreach2(HashMap hashMap, void (*visit)(void*,void*), void *param2);
void HashMap_Foreach3(HashMap hashMap, void (*visit)(void*,void*,void*), void *param3);
void HashMap_Foreach4(HashMap hashMap, void (*visit)(void*,void*,void*,void*), void *param3, void *param4);
#endif //DF347_HASHMAP_H
