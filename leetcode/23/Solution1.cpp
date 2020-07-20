#include "common.h"
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
// Assume that n represents the total number of nodes
// Time complexity: O(n)
// Space complexity: O(n)
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<int> vals;
        for(auto node: lists) {
            while(node) {
                vals.push_back(node->val);
                node = node->next;
            }
        }
        sort(vals.begin(), vals.end());
        ListNode dummy(0);
        auto it = &dummy;
        for(auto val: vals) {
            it->next = new ListNode(val);
            it = it->next;
        }
        return dummy.next;
    }    
};

#include "test.cpp"