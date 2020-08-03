
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
    ListNode* partition(ListNode* head, int x) {
        ListNode dummyLeft(0), dummyRight(0);
        auto left = &dummyLeft;
        auto right = &dummyRight;
        auto it = head;
        while (it) {
            if (it->val < x) {
                left->next = it;
                left = left->next;
            } else {
                right->next = it;
                right = right->next;
            }
            it = it->next;
        }
        left->next = dummyRight.next;
        right->next = nullptr;
        return dummyLeft.next;
    }
};
