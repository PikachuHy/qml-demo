
#include "gtest/gtest.h"
Solution s;
#define fun swapPairs
vector<int> fun(const vector<int> v) {
    auto ret = s.fun(toListNode(v));
    return toVector(ret);
}
TEST(LeetCode24SwapNodesInPairs, __LINE__) {
    vector<int> expect = {1, 2, 3, 4};
    auto ret = fun({2,1,4,3});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode24SwapNodesInPairs, __LINE__) {
    vector<int> expect = {1, 2, 3};
    auto ret = fun({2,1,3});
    EXPECT_EQ(ret, expect);
}