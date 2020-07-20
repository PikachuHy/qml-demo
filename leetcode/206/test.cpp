
#include "gtest/gtest.h"
Solution s;
vector<int> reverseList(const vector<int> v) {
    auto ret = s.reverseList(toListNode(v));
    return toVector(ret);
}
TEST(LeetCode206ReverseLinkedList, __LINE__) {
    vector<int> expect = {1, 2, 3, 4};
    auto ret = reverseList({4, 3, 2, 1});
    EXPECT_EQ(ret, expect);
}