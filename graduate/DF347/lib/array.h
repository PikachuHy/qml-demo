//
// Created by PikachuHy on 2019/10/14.
//

#ifndef DF347_ARRAY_H
#define DF347_ARRAY_H
typedef struct {
    int Size;
    int Capacity;
    int *Data;
} Array;
#define CreateArray(array, capacity) \
array.Size = 0; \
array.Capacity = capacity; \
array.Data = malloc(sizeof(int) * array.Capacity);

#define DisposeArray(array) \
free(array.Data);

#define EnsureCapacity(array, size) \
do { \
    if(array.Capacity < size) {\
        if(array.Capacity < 1024) array.Capacity *= 2;\
        else array.Capacity+=1024; \
        array.Data = realloc(array.Data, array.Capacity);\
    }    \
}while(0);

#define AppendData(array, data) \
do {\
EnsureCapacity(array, array.Size + 1) \
array.Data[array.Size] = data; \
array.Size++; \
} while(0);
#endif //DF347_ARRAY_H
