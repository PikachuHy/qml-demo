//
// Created by pikachu on 2019/7/16.
//
#include "solution.h"
#include "list.h"
#include "debug.h"
#include <stdlib.h>
#include <stdio.h>
int Josephus(int M, int N) {
    Info("Josephus Problem: M = %d, N = %d\n", M, N);
    List l = MakeEmpty(NULL);
    Position p = Header(l);
    for (int i = 0; i < N; ++i) {
        Insert(i+1, l, p);
        p = Next(p);
    }
    int ret = 0;
    p = First(l);
    while(!IsEmpty(l)) {
        for (int i = 0; i < M; ++i) {
            p = Next(p);
            if (p == l) {
                p = Next(p);
            }
        }
        ret = Retrieve(p);
        p = Next(p);
        Delete(ret, l);
    }
    return ret;
}