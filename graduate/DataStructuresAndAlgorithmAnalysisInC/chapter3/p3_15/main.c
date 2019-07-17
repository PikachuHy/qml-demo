//
// Created by pikachu on 2019/7/17.
//


#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "list.h"
#include "arraylist.h"
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
void test_Find() {
    List l = MakeEmpty(NULL);
    for (int i = 0; i <= 5; ++i) {
        Append(i, l);
    }
    char *s;
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->0->1->2->3->4->5")
    Find(3, l);
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->3->0->1->2->4->5")
    Find(5, l);
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->5->3->0->1->2->4")
    Find(0, l);
    s = ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->0->5->3->1->2->4")
}
void test_ArrayList_Find() {
    ArrayList l = MakeArrayList(NULL);
    for (int i = 0; i <= 5; ++i) {
        ArrayList_Append(i, l);
    }
    char *s;
    s = ArrayList_ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->0->1->2->3->4->5")
    ArrayList_Find(3, l);
    s = ArrayList_ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->3->0->1->2->4->5")
    ArrayList_Find(5, l);
    s = ArrayList_ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->5->3->0->1->2->4")
    ArrayList_Find(0, l);
    s = ArrayList_ToString(l);
    CU_ASSERT_STRING_EQUAL(s, "->0->5->3->1->2->4")
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
            (NULL == CU_add_test(pSuite, "test of Find()", test_Find))
            ||
            (NULL == CU_add_test(pSuite, "test of ArrayList_Find()", test_ArrayList_Find))
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