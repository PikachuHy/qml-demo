
#include "gtest/gtest.h"
Solution s;
#define fun reverseList
vector<int> fun(const vector<int> v) {
    auto ret = s.fun(toListNode(v));
    return toVector(ret);
}
TEST(LeetCode206ReverseLinkedList, __LINE__) {
    vector<int> expect = {1, 2, 3, 4};
    auto ret = fun({4, 3, 2, 1});
    EXPECT_EQ(ret, expect);
}