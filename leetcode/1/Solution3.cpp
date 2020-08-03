class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num2idx;
        for(int i=0;i<nums.size();i++) {
            int need_find = target - nums[i];
            if (num2idx.find(need_find) != num2idx.end()) {
                return {num2idx[need_find], i};
            } else {
                num2idx[nums[i]] = i;
            }
        }
        // error
        return {};
    }
};