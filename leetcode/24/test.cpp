
#include "gtest/gtest.h"
Solution s;
vector<int> swapPairs(const vector<int> v) {
    auto ret = s.swapPairs(toListNode(v));
    return toVector(ret);
}
TEST(LeetCode24SwapNodesInPairs, __LINE__) {
    vector<int> expect = {1, 2, 3, 4};
    auto ret = swapPairs({2,1,4,3});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode24SwapNodesInPairs, __LINE__) {
    vector<int> expect = {1, 2, 3};
    auto ret = swapPairs({2,1,3});
    EXPECT_EQ(ret, expect);
}