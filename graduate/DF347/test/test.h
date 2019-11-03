//
// Created by PikachuHy on 2019/10/13.
//

#ifndef DF347_TEST_H
#define DF347_TEST_H

#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include "memorypool.h"
void PrintTime(double time);
void PrintBool(bool X);
#define PRINT_PLACE printf("[%s]-%s:%s:%-5d", __TIMESTAMP__, __FUNCTION__, __FILE__, __LINE__);
/*

#define ASSERT_INT_EQUAL(ret, expected) \
{ \
clock_t begintime, endtime; \
begintime = clock(); \
int actual = ret; \
PRINT_PLACE \
if (actual == expected) { \
printf("\033[32mPASS\033[0m"); \
endtime = clock(); \
PrintTime(endtime-begintime); \
} else { \
printf("\033[31mFAIL\033[0m"); \
endtime = clock(); \
PrintTime(endtime-begintime); \
printf("expected: %d\n", expected); \
printf("actual: %d\n", actual); \
} \
}
*/

#define ASSERT_INT_EQUAL(ret, expected) \
\
    { \
        clock_t begintime, endtime; \
        begintime = clock(); \
        int actual = ret; \
        PRINT_PLACE \
        if (actual == expected) { \
            printf("\033[32mPASS\033[0m"); \
            endtime = clock(); \
            PrintTime(endtime - begintime); \
        } else { \
            printf("\033[31mFAIL\033[0m"); \
            endtime = clock(); \
            PrintTime(endtime - begintime); \
            printf("expected: %d\n", expected); \
            printf("actual: %d\n", actual); \
        } \
    }

#define ASSERT_TRUE(ret) \
\
    { \
        clock_t begintime, endtime; \
        begintime = clock(); \
        bool actual = ret; \
        PRINT_PLACE \
        if (actual) { \
            printf("\033[32mPASS\033[0m"); \
            endtime = clock(); \
            PrintTime(endtime - begintime); \
        } else { \
            printf("\033[31mFAIL\033[0m"); \
            endtime = clock(); \
            PrintTime(endtime - begintime); \
            printf("expected: true\n"); \
            printf("actual: false\n"); \
        } \
    }

#define ASSERT_FALSE(ret) \
\
    { \
        clock_t begintime, endtime; \
        begintime = clock(); \
        bool actual = ret; \
        PRINT_PLACE \
        if (!actual) { \
            printf("\033[32mPASS\033[0m"); \
            endtime = clock(); \
            PrintTime(endtime - begintime); \
        } else { \
            printf("\033[31mFAIL\033[0m"); \
            endtime = clock(); \
            PrintTime(endtime - begintime); \
            printf("expected: false\n"); \
            printf("actual: true\n"); \
        } \
    }

#endif //DF347_TEST_H
