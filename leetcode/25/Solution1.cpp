

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
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || !head->next) return head;
        ListNode dummy(0);
        auto it = &dummy;
        it->next = head;
        for(int i=0;i<k;i++) {
            if (!it->next) return head;
            it = it->next;
        }
        auto nextNode = it->next;
        ListNode* prev = nullptr;
        auto cur = head;
        while (cur && cur != nextNode) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head->next = reverseKGroup(nextNode, k);
        return prev;
    }
};
