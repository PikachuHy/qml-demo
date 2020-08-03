
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
// Space complexity: O(n) for creating a new linked list
//                   O(1) for applying in-place method
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        ListNode dummy(0);
        auto it = &dummy;
        int minIndex = 0;
        while (true) {
            minIndex = 0;
            for(int i=1;i<lists.size();i++) {
                if (!lists[i]) continue;
                if (!lists[minIndex]) {
                    minIndex = i;
                } else if (lists[minIndex]->val > lists[i]->val) {
                    minIndex = i;
                }
            }
            if (lists[minIndex]) {
                it->next = lists[minIndex];
                it = it->next;
                lists[minIndex] = lists[minIndex]->next;
            } else {
                break;
            }
        }
        it->next = nullptr;
        return dummy.next;
    }    
};

