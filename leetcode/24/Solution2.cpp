

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
// Space complexity: O(1)
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode dummy(0, head);
        auto it = &dummy;
        // first node
        auto p = head;
        // second node
        auto q = p->next;
        while (p && q) {
            auto next = q->next;
            it->next = q;
            q->next = p;
            it = p;
            p = next;
            if (p) q = p->next;
        }
        if (p) p->next = nullptr;
           
        it->next = p;
        return dummy.next;
    }
};

