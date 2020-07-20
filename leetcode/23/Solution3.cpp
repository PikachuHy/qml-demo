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
 // Assume that k, n represents the number of linked lists and nodes respectively
// Time complexity: O(nlogk)
// Space complexity: O(n) for creating a new linked list
//                   O(k) for applying in-place method
struct cmp
{
    bool operator() (ListNode* a, ListNode* b) 
    {
        return a->val > b->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        priority_queue<ListNode*, vector<ListNode*>, cmp> q;
        for (auto  it: lists) {
            if (it) q.push(it);
        }
        ListNode dummy(0);
        auto it = &dummy;
        while (!q.empty()) {
            it->next = q.top();
            q.pop();
            it = it->next;
            if (it->next) q.push(it->next);
        }
        it->next = nullptr;
        return dummy.next;
    }    
};

#include "test.cpp"