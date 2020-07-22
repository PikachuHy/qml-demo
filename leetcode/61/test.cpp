
#include "gtest/gtest.h"
Solution s;
vector<int> rotateRight(const vector<int>& a, int k) {
    auto ret = s.rotateRight(toListNode(a), k);
    return toVector(ret);
}
TEST(LeetCode61RotateRight, __LINE__) {
    vector<int> expect = {4, 5, 1, 2, 3};
    auto ret = rotateRight({1, 2, 3, 4, 5}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode61RotateRight, __LINE__) {
    vector<int> expect = {2, 0, 1};
    auto ret = rotateRight({0, 1, 2}, 4);
    EXPECT_EQ(ret, expect);
}