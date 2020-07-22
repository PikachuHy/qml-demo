
#include "gtest/gtest.h"
Solution s;
#define fun mergeKLists
vector<int> fun(const vector<vector<int>> lists) {
    auto nodes = toListNodes(lists);
    auto ret = s.fun(nodes);
    return toVector(ret);
}
TEST(LeetCode23MergeKLists, __LINE__) {
    vector<int> expect = {1, 1, 2, 3, 3};
    auto ret = fun({{1,2}, {3}, {1, 3}});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode23MergeKLists, __LINE__) {
    vector<int> expect = {1, 1, 2, 2, 2, 4, 5};
    auto ret = fun({{1,2,2}, {1, 4}, {2, 5}});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode23MergeKLists, __LINE__) {
    vector<int> expect = {};
    auto ret = fun({{}});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode23MergeKLists, __LINE__) {
    vector<int> expect = {};
    auto ret = fun({{}, {}});
    EXPECT_EQ(ret, expect);
}