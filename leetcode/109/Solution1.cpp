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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head, ListNode* end = nullptr) {
        if (head == end) return nullptr;
        if (head->next == end) return new TreeNode(head->val);
        auto mid = findMid(head, end);
        auto ret = new TreeNode(mid->val);
        ret->left = sortedListToBST(head, mid);
        ret->right = sortedListToBST(mid->next, end);
        return ret;
    }
    ListNode* findMid(ListNode* head, ListNode* end) {
        auto slow = head;
        auto fast = head;
        while (fast && fast != end &&
               fast->next && fast->next != end) {
            slow = slow->next;
            fast= fast->next->next;
        }
        return slow;
    }
};