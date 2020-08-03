

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
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        auto p = head;
        auto q = p->next;
        auto next = q->next;
        q->next = p;
        p->next = swapPairs(next);
        return q;
    }
};
