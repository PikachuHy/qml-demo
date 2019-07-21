//
// Created by pikachu on 2019/7/21.
//


#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "deque.h"
#include <stdlib.h>
/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite()
{
    return 0;
}

/* The suite cleanup function.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite()
{
    return 0;
}

void test_Deque() {
    Deque d = CreateDeque(5);
    char* s;
    int front;
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "");
    Inject(1, d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "1<-");
    front = Front(d);
    CU_ASSERT_EQUAL(front, 1);
    Eject(d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "");
    Push(1, d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "1<-");
    Push(0,d);
    front = Front(d);
    CU_ASSERT_EQUAL(front, 0);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "0<-1<-")
    Pop(d);
    Inject(2, d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "1<-2<-");
    Inject(3, d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "1<-2<-3<-");
    Pop(d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-");
    front = Front(d);
    CU_ASSERT_EQUAL(front, 2);
    Inject(4, d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-4<-");
    Inject(5, d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-4<-5<-");
    Pop(d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "3<-4<-5<-");
    Inject(6, d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "3<-4<-5<-6<-");
    Eject(d);
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "3<-4<-5<-");
    while(!IsEmpty(d)) {
        Eject(d);
    }
    s = ToString(d);
    CU_ASSERT_STRING_EQUAL(s, "");
}

int main() {
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if (
            (NULL == CU_add_test(pSuite, "test of Deque()", test_Deque))
            )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
//    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_set_mode(CU_BRM_NORMAL);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}