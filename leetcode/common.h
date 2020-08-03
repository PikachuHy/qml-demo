
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <variant>
#define CAT2(x, y) x##y
#define CAT1(x,y) CAT2(x, y)
#define TESTCAST_CLASSNAME CAT1(LeetCode, DIR_FILENAME)
#define STR1(R) #R
#define STR2(R) STR1(R)
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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
vector<ListNode*> toListNodes(const vector<vector<int>> & vs) {
    vector<ListNode*> ret;
    for(const auto & it: vs) {
        ret.push_back(toListNode(it));
    }
    return ret;
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


vector<variant<int, string>> toVector(TreeNode *root) {
    vector<variant<int, string>> ret;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        if (front == nullptr) {
            if (!q.empty())
                ret.emplace_back("null");
        } else {
            ret.emplace_back(front->val);
            if (front->left || front->right) {
                q.push(front->left);
                q.push(front->right);
            }
        }
    }
    return ret;
}

template<typename... T>
ostream& operator <<(ostream& out, const vector<variant<T...>>& vec) {
    for (const auto &it: vec) {
        auto f = [&out](auto &x) { out << x <<" "; };
        visit(f, it);
    }
    return out;
}
template<typename... T>
ostream& operator <<(ostream& out, const variant<T...>& v) {
    auto f = [&out](auto &x) { out << x <<" "; };
    visit(f, v);
    return out;
}