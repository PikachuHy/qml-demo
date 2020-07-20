
#include "gtest/gtest.h"
Solution s;
vector<int> mergeTwoLists(const vector<int>& a, const vector<int>& b) {
    auto ret = s.mergeTwoLists(toListNode(a), toListNode(b));
    return toVector(ret);
}
TEST(LeetCode21MergeTwoLists, __LINE__) {
    vector<int> expect = {1, 1, 2, 2, 3, 3};
    auto ret = mergeTwoLists({1,2,3}, {1, 2, 3});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode21MergeTwoLists, __LINE__) {
    vector<int> expect = {1,2,3};
    auto ret = mergeTwoLists({1}, {2, 3});
    EXPECT_EQ(ret, expect);
}