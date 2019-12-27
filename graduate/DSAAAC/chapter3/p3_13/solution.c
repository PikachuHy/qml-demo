//
// Created by pikachu on 2019/7/17.
//
#include "solution.h"
#include "list.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
int NumberWidth(int n) {
    int width = 0;
    while(n!=0) {
        n = n /10;
        width++;
    }
    return width;
}
int MaxWidth(int* in, int len) {
    int max = 0;
    for (int i = 0; i < len; ++i) {
        int width = NumberWidth(in[i]);
        if (width > max) {
            max = width;
        }
    }
    return max;
}
int CalculateBucket(int data, int n) {
    for (int i = 0; i < n; ++i) {
        data = data / 10;
    }
    return data % 10;
}
int* CardSort(int* in, int len) {
    int M;
    List *arr;
    int  *out;
    M = 10;
    arr = malloc(sizeof(List) * M);
    out = malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) {
        out[i] = in[i];
    }
    for (int i = 0; i < M; ++i) {
        arr[i] = MakeEmpty(NULL);
    }
    int n = MaxWidth(in, len);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < len; ++j) {
            int data = out[j];
            int bucket = CalculateBucket(data, i);
            Append(data, arr[bucket]);
        }
        // Collect
        int index = 0;
        for (int j = 0; j < M; ++j) {
            List l = arr[j];
            while(!IsEmpty(l)) {
                Position p = First(l);
                int data = Retrieve(p);
                out[index++] = data;
                Delete(data, l);
            }
        }
        Debug("Collect[%d]:", i);
        for (int j = 0; j < len; ++j) {
            printf(",%d",out[j]);
        }
        printf("\n");
    }
    return out;
}