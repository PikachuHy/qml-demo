
#include "gtest/gtest.h"
Solution s;
#define fun deleteDuplicates
vector<int> fun(const vector<int>& a) {
    auto ret = s.fun(toListNode(a));
    return toVector(ret);
}
TEST(LeetCode82RemoveDuplicatesfromSortedListII, __LINE__) {
    vector<int> expect = {1,2,5};
    auto ret = fun({1,2,3,3,4,4,5});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode82RemoveDuplicatesfromSortedListII, __LINE__) {
    vector<int> expect = {2, 3};
    auto ret = fun({1,1,1,2,3});
    EXPECT_EQ(ret, expect);
}