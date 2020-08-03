

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
        auto begin = head;
        auto tail = head;
        auto it = head;
        head = nullptr;
        do {
            for(int i=0;i<k;i++) {
                if (!it) {
                    tail->next = begin;
                    return head;
                }
                it = it->next;
            }
            if (head == nullptr) {
                head = reverseList(begin, it);
            } else {
                tail->next = reverseList(begin, it);
                tail = begin;
            }
            begin = it;
        } while(true);
        return head;
    }
    ListNode* reverseList(ListNode* begin, ListNode* end) {
        ListNode* prev = nullptr;
        auto cur = begin;
        while (cur && cur != end) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

