//
// Created by pikachu on 2019/7/18.
//


#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "arrayqueue.h"
#include "queue.h"
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

void test_ArrayQueue() {
    ArrayQueue q = CreateArrayQueue(5);
    char* s;
    int front;
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "");
    ArrayQueue_Enqueue(1, q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "1<-");
    front = ArrayQueue_Front(q);
    CU_ASSERT_EQUAL(front, 1);
    ArrayQueue_Enqueue(2, q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "1<-2<-");
    ArrayQueue_Enqueue(3, q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "1<-2<-3<-");
    ArrayQueue_Dequeue(q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-");
    front = ArrayQueue_Front(q);
    CU_ASSERT_EQUAL(front, 2);
    ArrayQueue_Enqueue(4, q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-4<-");
    ArrayQueue_Enqueue(5, q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-4<-5<-");
    ArrayQueue_Dequeue(q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "3<-4<-5<-");
    ArrayQueue_Enqueue(6, q);
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "3<-4<-5<-6<-");
    while(!ArrayQueue_IsEmpty(q)) {
        ArrayQueue_Dequeue(q);
    }
    s = ArrayQueue_ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "");
}
void test_Queue() {
    Queue q = CreateQueue(5);
    char* s;
    int front;
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "");
    Enqueue(1, q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "1<-");
    front = Front(q);
    CU_ASSERT_EQUAL(front, 1);
    Enqueue(2, q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "1<-2<-");
    Enqueue(3, q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "1<-2<-3<-");
    Dequeue(q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-");
    front = Front(q);
    CU_ASSERT_EQUAL(front, 2);
    Enqueue(4, q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-4<-");
    Enqueue(5, q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "2<-3<-4<-5<-");
    Dequeue(q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "3<-4<-5<-");
    Enqueue(6, q);
    s = ToString(q);
    CU_ASSERT_STRING_EQUAL(s, "3<-4<-5<-6<-");
    while(!IsEmpty(q)) {
        Dequeue(q);
    }
    s = ToString(q);
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
            (NULL == CU_add_test(pSuite, "test of ArrayQueue()", test_ArrayQueue))
            ||
            (NULL == CU_add_test(pSuite, "test of Queue()", test_Queue))
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