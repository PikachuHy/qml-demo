
#include "gtest/gtest.h"
Solution s;
vector<int> removeNthFromEnd(const vector<int>& a, int n) {
    auto ret = s.removeNthFromEnd(toListNode(a), n);
    return toVector(ret);
}
TEST(LeetCode19RemoveNthFromEnd, __LINE__) {
    vector<int> expect = {1, 2, 3, 5};
    auto ret = removeNthFromEnd({1,2,3,4,5}, 2);
    EXPECT_EQ(ret, expect);
}