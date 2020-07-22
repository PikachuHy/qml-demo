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
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !head->next) return head;
        int count = 0;
        auto it = head;
        while (it) {
            count++;
            it = it->next;
        }
        k = k % count;
        k = count - k;
        it = head;
        ListNode* newTail = nullptr;
        // i = 1, for it pointer to head
        for(int i=1;i<k;i++) {
            it = it->next;
        }
        newTail = it;
        while(it->next) it = it->next;
        it->next = head;
        head = newTail->next;
        newTail->next = nullptr;
        return head;
    }
};

#include "test.cpp"