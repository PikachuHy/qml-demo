
#include "gtest/gtest.h"
Solution s;
#define fun reverseKGroup
vector<int> fun(const vector<int> v, int k) {
    auto ret = s.fun(toListNode(v), k);
    return toVector(ret);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1};
    auto ret = fun({1}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2};
    auto ret = fun({2,1}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2, 3};
    auto ret = fun({2,1, 3}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2, 3, 4};
    auto ret = fun({2,1, 4, 3}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2, 3, 4, 5};
    auto ret = fun({2,1, 4, 3, 5}, 2);
    EXPECT_EQ(ret, expect);
}
