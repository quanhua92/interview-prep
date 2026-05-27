/*
 * P572: Subtree of Another Tree [PREMIUM] (Easy)
 * https://leetcode.com/problems/subtree-of-another-tree/
 * Topics: Tree, Depth-First Search, String Matching, Binary Tree, Hash Function
 */

#include "io.h"
#include <queue>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

static TreeNode *from_list(const std::vector<int>& vals) {
    if (vals.empty() || vals[0] == 2147483647) return nullptr;
    TreeNode *root = new TreeNode(vals[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode *node = q.front(); q.pop();
        if (i < vals.size()) {
            if (vals[i] != 2147483647) { node->left = new TreeNode(vals[i]); q.push(node->left); }
            i++;
        }
        if (i < vals.size()) {
            if (vals[i] != 2147483647) { node->right = new TreeNode(vals[i]); q.push(node->right); }
            i++;
        }
    }
    return root;
}

static bool is_same(TreeNode *a, TreeNode *b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    return a->val == b->val && is_same(a->left, b->left) && is_same(a->right, b->right);
}

static bool isSubtree(TreeNode *root, TreeNode *subRoot) {
    if (!subRoot) return true;
    if (!root) return false;
    if (is_same(root, subRoot)) return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

int main() {
    auto root_line = read_line();
    auto sub_line = read_line();
    auto parse = [](const std::string& s) -> std::vector<int> {
        std::vector<int> v;
        size_t pos = 0;
        while (pos < s.size()) {
            while (pos < s.size() && s[pos] == ' ') pos++;
            size_t end = s.find(' ', pos);
            if (end == std::string::npos) end = s.size();
            std::string tok = s.substr(pos, end - pos);
            pos = end;
            v.push_back(tok == "null" ? 2147483647 : std::stoi(tok));
        }
        return v;
    };
    TreeNode *root = from_list(parse(root_line));
    TreeNode *sub = from_list(parse(sub_line));
    write_bool(isSubtree(root, sub));
    return 0;
}
