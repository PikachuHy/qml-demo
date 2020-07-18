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
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr) return head;
        ListNode dummy(0);
        dummy.next = head;
        auto it = head;
        int nodeCount = 0;
        while (it) {
            nodeCount++;
            it = it->next;
        }
        int nodeIndexToBeDeleted = nodeCount - n;
        it = &dummy;
        for(int i=0;i<nodeIndexToBeDeleted; i++) {
            it = it->next;
        }
        auto nodeToBeDeleted = it->next;
        it->next = nodeToBeDeleted->next;
        delete nodeToBeDeleted;

        return dummy.next;
    }
};
#include "test.cpp"