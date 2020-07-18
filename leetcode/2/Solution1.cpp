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
// Time complexity: O(max(m, n))
// Space complexity: O(max(m, n))
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        auto it = &dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            int sum = 0;
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            carry = sum / 10;
            sum = sum % 10;
            it->next= new ListNode(sum);
            it = it->next;
        }
        return dummy.next;
    }
};

#include "test.cpp"