
#include "gtest/gtest.h"
Solution s;
#define fun removeNthFromEnd
vector<int> fun(const vector<int>& a, int n) {
    auto ret = s.fun(toListNode(a), n);
    return toVector(ret);
}
TEST(LeetCode19RemoveNthFromEnd, __LINE__) {
    vector<int> expect = {1, 2, 3, 5};
    auto ret = fun({1,2,3,4,5}, 2);
    EXPECT_EQ(ret, expect);
}