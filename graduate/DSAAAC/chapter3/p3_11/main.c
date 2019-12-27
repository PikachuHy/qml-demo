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
void test_FindRecursion() {
    List L = MakeEmpty(NULL);
    for (int i = 0; i < 10000000; ++i) {
        Insert(i, L, NULL);
        Position p = FindRecursion(i, L);
        CU_ASSERT_NOT_EQUAL(p, NULL);
    }
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
            (NULL == CU_add_test(pSuite, "test of FindRecursion()", test_FindRecursion))
            )
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}