//
// Created by pikachu on 2019/7/16.
//

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "tree.h"

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
void test_SearchTree() {
    SearchTree tree = CreateTree();
    char *s = NULL;
    s = ToString(tree);
    CU_ASSERT_STRING_EQUAL(s, "");
    tree = Insert(6, tree);
    s = ToString(tree);
    CU_ASSERT_STRING_EQUAL(s, ",6")
    tree = Insert(2, tree);
    s = ToString(tree);
    CU_ASSERT_STRING_EQUAL(s, ",2,6")
    tree = Insert(8, tree);
    s = ToString(tree);
    CU_ASSERT_STRING_EQUAL(s, ",2,6,8")
    tree = Insert(1, tree);
    tree = Insert(4, tree);
    tree = Insert(3, tree);
    s = ToString(tree);
    CU_ASSERT_STRING_EQUAL(s, ",1,2,3,4,6,8")
    int max = Retrieve(FindMax(tree));
    CU_ASSERT_EQUAL(max, 8);
    int min = Retrieve(FindMin(tree));
    CU_ASSERT_EQUAL(min, 1);
    tree = Delete(1, tree);
    s = ToString(tree);
    CU_ASSERT_STRING_EQUAL(s, ",2,3,4,6,8")
    min = Retrieve(FindMin(tree));
    CU_ASSERT_EQUAL(min, 2);
    tree = Delete(2, tree);
    s = ToString(tree);
    CU_ASSERT_STRING_EQUAL(s, ",3,4,6,8")

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
            (NULL == CU_add_test(pSuite, "test of SearchTree()", test_SearchTree))
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