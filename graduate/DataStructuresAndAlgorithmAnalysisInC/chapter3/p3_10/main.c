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
void test_ToString() {
    List L = MakeEmpty(NULL);
    CU_ASSERT_STRING_EQUAL(ToString(L), "");
    Position p = Header(L);
    Insert(1, L, p);
    char* s = ToString(L);

    CU_ASSERT_STRING_EQUAL(ToString(L), "->1");
    p = Next(p);
    Insert(2, L, p);
    CU_ASSERT_STRING_EQUAL(ToString(L), "->1->2");
    p = Next(p);
    Insert(3, L, p);
    CU_ASSERT_STRING_EQUAL(ToString(L), "->1->2->3");
}
void test_Delete() {
    List L = MakeEmpty(NULL);
    Position p = Header(L);
    Insert(1, L, p);
    p = Next(p);
    Insert(2, L, p);
    p = Next(p);
    Insert(3, L, p);
    Delete(2, L);
    CU_ASSERT_STRING_EQUAL(ToString(L), "->1->3");
    Delete(1, L);
    CU_ASSERT_STRING_EQUAL(ToString(L), "->3");
    Delete(3, L);
    CU_ASSERT_STRING_EQUAL(ToString(L), "");

}
void test_Josephus() {
    CU_ASSERT_EQUAL(Josephus(0, 5), 5);
    CU_ASSERT_EQUAL(Josephus(0, 50), 50);
    CU_ASSERT_EQUAL(Josephus(0, 500), 500);
    CU_ASSERT_EQUAL(Josephus(0, 5000), 5000);
    CU_ASSERT_EQUAL(Josephus(0, 50000), 50000);
    CU_ASSERT_EQUAL(Josephus(1, 5), 3);
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
            (NULL == CU_add_test(pSuite, "test of ToString()", test_ToString))
            ||
            (NULL == CU_add_test(pSuite, "test of Delete()", test_Delete))
            ||
            (NULL == CU_add_test(pSuite, "test of Josephus()", test_Josephus))

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