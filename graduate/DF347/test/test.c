//
// Created by PikachuHy on 2019/10/13.
//

#include "test.h"
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

void PrintTime(double time) {
    printf(" %fs\n", time / CLOCKS_PER_SEC);
}

void PrintBool(bool X) {
    if(X){
        printf("true");
    } else {
        printf("false");
    }
}
