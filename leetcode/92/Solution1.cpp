
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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (!head || !head->next) return head;
        ListNode dummy(0);
        dummy.next = head;
        auto cur = head;
        ListNode* prev = &dummy;
        int i = 1;
        for(;i<m;i++) {
            prev = cur;
            cur=cur->next;
        }
        auto lastTail = prev;
        auto newTail = cur;
        prev = nullptr;
        for(;i<=n;i++) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        lastTail->next = prev;
        newTail->next = cur;
        return dummy.next;
    }
};
