class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int N = nums.size();
        unordered_map<int, int> num2idx;
        for(int i=0;i<N;i++) {
            num2idx[nums[i]] = i;
        }
        for(int i=0;i<N;i++) {
            int need_find = target - nums[i];
            if (num2idx.find(need_find)!=num2idx.end() && num2idx[need_find] != i) {
                return {i, num2idx[need_find]};
            }
        }
        // error;
        return {};
    }
};