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
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode dummy(0);
        auto it = &dummy;
        it->next = head;
        while (it->next) {
            if (!it->next->next) break;
            if (it->next->val == it->next->next->val) {
                auto t = it->next->next;
                while (t->next && t->next->val == it->next->val) t = t->next;
                it->next = t->next;
            } else {
                it = it->next;
            }
        }
        return dummy.next;
    }
};

#include "test.cpp"