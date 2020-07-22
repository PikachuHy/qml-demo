
#include "gtest/gtest.h"
Solution s;
vector<int> deleteDuplicates(const vector<int>& a) {
    auto ret = s.deleteDuplicates(toListNode(a));
    return toVector(ret);
}
TEST(LeetCode82RemoveDuplicatesfromSortedListII, __LINE__) {
    vector<int> expect = {1,2,5};
    auto ret = deleteDuplicates({1,2,3,3,4,4,5});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode82RemoveDuplicatesfromSortedListII, __LINE__) {
    vector<int> expect = {2, 3};
    auto ret = deleteDuplicates({1,1,1,2,3});
    EXPECT_EQ(ret, expect);
}