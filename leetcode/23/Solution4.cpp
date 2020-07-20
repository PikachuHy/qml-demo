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
// Time complexity: O(kn)
// Space complexity: O(1)
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
        ListNode *ret = lists[0];
        for(int i=1;i<lists.size();i++) {
            ret = merge(ret, lists[i]);
        }
        return ret;
    }
    ListNode* merge(ListNode* a, ListNode* b) {
        if (!b) return a;
        if (!a) return b;
        ListNode dummy(0);
        auto it = &dummy;
        while (a && b) {
            if (a->val < b->val) {
                it->next = a;
                a = a->next;
            } else {
                it->next = b;
                b = b->next;
            }
            it = it->next;
        }
        while (a) {
            it->next = a;
            it = it->next;
            a = a->next;
        }
        while (b) {
            it->next = b;
            it = it->next;
            b = b->next;
        }
        it->next = nullptr;
        return dummy.next;
    }
};

#include "test.cpp"