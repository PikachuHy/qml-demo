
#include "gtest/gtest.h"
Solution s;
#define fun reverseBetween
vector<int> fun(const vector<int>& a, int m, int n) {
    auto ret = s.fun(toListNode(a), m, n);
    return toVector(ret);
}

TEST(LeetCode92ReverseBetween, __LINE__) {
    vector<int> expect = {1,4,3,2,5};
    auto ret = fun({1,2,3,4,5}, 2, 4);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode92ReverseBetween, __LINE__) {
    vector<int> expect = {4,3,2,1, 5};
    auto ret = fun({1,2,3,4,5}, 1, 4);
    EXPECT_EQ(ret, expect);
}