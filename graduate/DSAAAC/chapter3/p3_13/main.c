//
// Created by pikachu on 2019/7/17.
//


#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "solution.h"
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
char* ArrayToString(int *arr, int len) {
    char str[1000] = "";
    for (int i = 0; i < len; ++i) {
        sprintf(str, "%s,%d", str, arr[i]);
    }
    char *ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}
void test_CardSort() {
    int arr[] = {
            64,8,216,512,27,729,0,1,343,125
    };
    int *ret;
    char *s;
    ret = CardSort(arr, 10);
    s = ArrayToString(ret, 10);
    CU_ASSERT_STRING_EQUAL(s, ",0,1,8,27,64,125,216,343,512,729");
    ret = CardSort(arr, 1);
    s = ArrayToString(ret, 1);
    CU_ASSERT_STRING_EQUAL(s, ",64");
    ret = CardSort(arr, 2);
    s = ArrayToString(ret, 2);
    CU_ASSERT_STRING_EQUAL(s, ",8,64");
    ret = CardSort(arr, 3);
    s = ArrayToString(ret, 3);
    CU_ASSERT_STRING_EQUAL(s, ",8,64,216");
    ret = CardSort(arr, 4);
    s = ArrayToString(ret, 4);
    CU_ASSERT_STRING_EQUAL(s, ",8,64,216,512");
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
            (NULL == CU_add_test(pSuite, "test of CardSort()", test_CardSort))
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