#include "gtest/gtest.h"
Solution s;
#define fun twoSum
vector<int> fun(vector<int> nums, int target) {
    auto ret = s.fun(nums, target);
    return ret;
}
TEST(TESTCAST_CLASSNAME, __LINE__) {
    vector<int> expect = {0, 1};
    auto ret = fun({2,7,11,15}, 9);
    EXPECT_EQ(ret, expect);
}