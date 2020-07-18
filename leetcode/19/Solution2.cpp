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
// Assume that L represents the length of head
// Time complexity: O(L)
// Space complexity: O(1)
// One pass
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr) return head;
        ListNode dummy(0);
        dummy.next = head;
        auto slow = &dummy;
        auto fast = &dummy;
        for(int i=0;i<n;i++) fast = fast->next;
        while(fast && fast->next!=nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
        auto nodeToBeDeleted = slow->next;
        slow->next = nodeToBeDeleted->next;
        delete nodeToBeDeleted;
        return dummy.next;
    }
};
#include "test.cpp"