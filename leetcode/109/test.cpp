
#include "gtest/gtest.h"
Solution s;
#define fun sortedListToBST
vector<variant<int, string>> fun(const vector<int>& a) {
    auto ret = s.fun(toListNode(a));
    return toVector(ret);
}

TEST(LeetCode109SortedListToBST, __LINE__) {
    vector<variant<int, string>> expect = {0,-3,9,-10,"null",5};
    auto ret = fun({-10,-3,0,5,9});
    EXPECT_EQ(ret, expect);
}
