//
// Created by pikachu on 2019/7/17.
//


#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "list.h"
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
void test_LazyDeleteList() {
    List l = MakeEmpty(NULL);
    for (int i = 0; i < 5; ++i) {
        Append(i, l);
    }
    char *s;
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->0->1->2->3->4");
    Delete(3, l);
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(s,"->0->1->2->4")
    Delete(1, l);
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->0->2->4");
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
            (NULL == CU_add_test(pSuite, "test of LazyDeleteList()", test_LazyDeleteList))
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