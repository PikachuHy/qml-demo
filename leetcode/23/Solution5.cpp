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
// Assume that k, n represents the number of linked lists and nodes respectively
// Time complexity: O(nlogk)
// Space complexity: O(1)
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        if (lists.size() == 1) return lists[0];
        if (lists.size() % 2 == 1) lists.push_back(nullptr);
        vector<ListNode*> mergedList;
        for(int i=0;i<lists.size();i+=2) {
            mergedList.push_back(mergeTwoLists(lists[i], lists[i+1]));
        }
        return mergeKLists(mergedList);
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        ListNode dummy(0);
        auto it = &dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                it->next = l1;
                l1 = l1->next;
            } else {
                it->next = l2;
                l2 = l2->next;
            }
            it = it->next;
        }
        it->next = l1 ? l1 : l2;
        return dummy.next;
    }    
};
#include "test.cpp"