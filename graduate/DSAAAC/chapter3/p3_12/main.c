//
// Created by pikachu on 2019/7/16.
//

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "solution.h"
#include "list.h"
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
void test_Reserve() {
    char* s;
    List l = MakeEmpty(NULL);
    l = Reserve(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "");
    Insert(1, l, NULL);
    l = Reserve(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->1");
    Insert(2, l, NULL);
    s = ToString(l);
    l = Reserve(l);
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->1->2");
    Insert(3, l, NULL);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->3->1->2");
    l = Reserve(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->2->1->3");
}
void test_ReserveByStack() {
    char* s;
    List l = MakeEmpty(NULL);
    l = ReserveByStack(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "");
    Insert(1, l, NULL);
    l = ReserveByStack(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->1");
    Insert(2, l, NULL);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->2->1");
    s = ToString(l);
    l = ReserveByStack(l);
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->1->2");
    Insert(3, l, NULL);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->3->1->2");
    l = ReserveByStack(l);
    CU_ASSERT_STRING_EQUAL(ToString(l), "->2->1->3");
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
            (NULL == CU_add_test(pSuite, "test of Reserve()", test_Reserve))
            ||
            (NULL == CU_add_test(pSuite, "test of ReserveByStack()", test_ReserveByStack))
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