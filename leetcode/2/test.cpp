
#include "gtest/gtest.h"
Solution s;
vector<int> addTwoNumbers(const vector<int>& a, const vector<int>& b) {
    auto ret = s.addTwoNumbers(toListNode(a), toListNode(b));
    return toVector(ret);
}
TEST(LeetCode2AddTwoNumbers, __LINE__) {
    vector<int> expect = {4, 4, 4};
    auto ret = addTwoNumbers({1,2,3}, {3, 2, 1});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode2AddTwoNumbers, __LINE__) {
    vector<int> expect = {4, 4, 3};
    auto ret = addTwoNumbers({1,2,2}, {3, 2, 1});
    EXPECT_EQ(ret, expect);
}