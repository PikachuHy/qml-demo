//
// Created by PikachuHy on 2019/10/13.
//
#include "../lib/util.h"
#include "test.h"

void test1() {
    int date = 0;
    sdate2idate(date, "1996-01-02")
    ASSERT_INT_EQUAL(date, 19960102)
}

void test2() {
    int date = 0;
    sdate2idate(date, "1996-12-01")
    ASSERT_INT_EQUAL(date, 19961201)
}

int main() {
    test1();
    test2();
}