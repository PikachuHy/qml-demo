//
// Created by PikachuHy on 2019/10/18.
//

#ifndef DF347_LOG_H
#define DF347_LOG_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define DEBUG(fmt, ...) printf("[DEBUG] "); printf(fmt, ##__VA_ARGS__); printf("\n")
#define ERROR(fmt, ...) printf("[ERROR] "); printf(fmt, ##__VA_ARGS__); printf("\n")
#endif //DF347_LOG_H
