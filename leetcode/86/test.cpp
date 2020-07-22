
#include "gtest/gtest.h"
Solution s;
#define fun partition
vector<int> fun(const vector<int>& a, int x) {
    auto ret = s.fun(toListNode(a), x);
    return toVector(ret);
}
TEST(LeetCode86PartitionList, __LINE__) {
    vector<int> expect = {1,2,2,4,3,5};
    auto ret = fun({1,4,3,2,5,2}, 3);
    EXPECT_EQ(ret, expect);
}