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
// Assume that m and n represents the length of l1 and l2 respectively
// Time complexity: O(m+n)
// Space complexity: O(1)
class Solution {
public:
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