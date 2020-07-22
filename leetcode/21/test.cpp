
#include "gtest/gtest.h"
Solution s;
#define fun mergeTwoLists
vector<int> fun(const vector<int>& a, const vector<int>& b) {
    auto ret = s.fun(toListNode(a), toListNode(b));
    return toVector(ret);
}
TEST(LeetCode21MergeTwoLists, __LINE__) {
    vector<int> expect = {1, 1, 2, 2, 3, 3};
    auto ret = fun({1,2,3}, {1, 2, 3});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode21MergeTwoLists, __LINE__) {
    vector<int> expect = {1,2,3};
    auto ret = fun({1}, {2, 3});
    EXPECT_EQ(ret, expect);
}