//
// Created by pikachu on 2019/7/25.
//

#include "test.h"
#include "BinHeap.h"
void test_BinHeap();
void InitTest(CU_pSuite pSuite) {
    if (pSuite == NULL) {
        Fatal("CU_pSuite is NULL\n");
        exit(1);
    }
    if (
            (NULL == CU_add_test(pSuite, "test of BinHeap()", test_BinHeap))
            )
    {
        CU_cleanup_registry();
        exit(CU_get_error());
    }
}
void test_BinHeap() {
    PriorityQueue h;
    h = Initialize(20);
    char *s;
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, "");
    Insert(10, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",10")
    Insert(12, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",10,12")
    Insert(1, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,12,10")
    Insert(14, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,12,10,14")
    Insert(6, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,6,10,14,12")
    Insert(5, h);
    Insert(8, h);
    Insert(15, h);
    Insert(3, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,3,5,6,12,10,8,15,14")
    Insert(9, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,3,5,6,9,10,8,15,14,12")
    Insert(7, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,3,5,6,7,10,8,15,14,12,9")
    Insert(4, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,3,4,6,7,5,8,15,14,12,9,10")
    Insert(11, h);
    Insert(13, h);
    Insert(2, h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",1,3,2,6,7,5,4,15,14,12,9,10,11,13,8")
    DeleteMin(h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",2,3,4,6,7,5,8,15,14,12,9,10,11,13")
    DeleteMin(h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",3,6,4,13,7,5,8,15,14,12,9,10,11")
    DeleteMin(h);
    s = ToString(h);
    CU_ASSERT_STRING_EQUAL(s, ",4,6,5,13,7,10,8,15,14,12,9,11")
}