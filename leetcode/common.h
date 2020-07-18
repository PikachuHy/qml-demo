
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* toListNode(const vector<int> & v) {
    ListNode dummy(0);
    auto it = &dummy;
    for(auto val: v) {
        it->next = new ListNode(val);
        it = it->next;
    }
    return dummy.next;
}

vector<int> toVector(ListNode *l) {
    if (l == nullptr) return {};
    vector<int> ret;
    while (l) {
        ret.push_back(l->val);
        l = l->next;
    }
    return ret;
}