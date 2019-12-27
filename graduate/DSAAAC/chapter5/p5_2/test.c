//
// Created by pikachu on 2019/7/25.
//

#include "test.h"
#include "HashSep.h"
void test_HashSep();
void InitTest(CU_pSuite pSuite) {
    if (pSuite == NULL) {
        Fatal("CU_pSuite is NULL\n");
        exit(1);
    }
    if (
            (NULL == CU_add_test(pSuite, "test of HashSep()", test_HashSep))
            )
    {
        CU_cleanup_registry();
        exit(CU_get_error());
    }
}
void test_HashSep() {
    HashTable H;
    H = InitializeTable(5);
    char *s;
    s = ToString(H);
    CU_ASSERT_STRING_EQUAL(s, "->[]->[]->[]->[]->[]")
    Insert(0, H);
    s = ToString(H);
    CU_ASSERT_STRING_EQUAL(s, "->[->0]->[]->[]->[]->[]")
    Insert(81, H);
    s = ToString(H);
    CU_ASSERT_STRING_EQUAL(s, "->[->0]->[->81]->[]->[]->[]")
    Insert(1, H);
    s = ToString(H);
    CU_ASSERT_STRING_EQUAL(s, "->[->0]->[->1->81]->[]->[]->[]")
    Insert(64, H);
    s = ToString(H);
    CU_ASSERT_STRING_EQUAL(s, "->[->0]->[->1->81]->[]->[]->[->64]")
    Insert(4, H);
    s = ToString(H);
    CU_ASSERT_STRING_EQUAL(s, "->[->0]->[->1->81]->[]->[]->[->4->64]")
    Position p;
    p = Find(1, H);
    CU_ASSERT_NOT_EQUAL(p, NULL);
    p = Find(10, H);
    CU_ASSERT_EQUAL(p, NULL);
}