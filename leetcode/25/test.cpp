
#include "gtest/gtest.h"
Solution s;
vector<int> reverseKGroup(const vector<int> v, int k) {
    auto ret = s.reverseKGroup(toListNode(v), k);
    return toVector(ret);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1};
    auto ret = reverseKGroup({1}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2};
    auto ret = reverseKGroup({2,1}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2, 3};
    auto ret = reverseKGroup({2,1, 3}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2, 3, 4};
    auto ret = reverseKGroup({2,1, 4, 3}, 2);
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode25ReverseKGroup, __LINE__) {
    vector<int> expect = {1, 2, 3, 4, 5};
    auto ret = reverseKGroup({2,1, 4, 3, 5}, 2);
    EXPECT_EQ(ret, expect);
}
