
#include "gtest/gtest.h"
Solution s;
vector<int> mergeKLists(const vector<vector<int>> lists) {
    auto nodes = toListNodes(lists);
    auto ret = s.mergeKLists(nodes);
    return toVector(ret);
}
TEST(LeetCode2MergeKLists, __LINE__) {
    vector<int> expect = {1, 1, 2, 3, 3};
    auto ret = mergeKLists({{1,2}, {3}, {1, 3}});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode2MergeKLists, __LINE__) {
    vector<int> expect = {1, 1, 2, 2, 2, 4, 5};
    auto ret = mergeKLists({{1,2,2}, {1, 4}, {2, 5}});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode23MergeKLists, __LINE__) {
    vector<int> expect = {};
    auto ret = mergeKLists({{}});
    EXPECT_EQ(ret, expect);
}

TEST(LeetCode23MergeKLists, __LINE__) {
    vector<int> expect = {};
    auto ret = mergeKLists({{}, {}});
    EXPECT_EQ(ret, expect);
}