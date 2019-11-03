//
// Created by PikachuHy on 2019/10/14.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main() {
    /**
     * 10亿int 大概4GB
     */
    long size = 10 * 1000 * 1000l * 1000;
    int * ret = malloc(sizeof(int) * size);
    while (true) {
        for (int i = 0; i < size; ++i) {
            ret[i] = 0;
        }
    }
    free(ret);
    return 0;
}