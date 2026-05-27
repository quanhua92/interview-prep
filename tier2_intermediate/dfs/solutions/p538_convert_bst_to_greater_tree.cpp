/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 */

#include "io.h"
#include <cstdio>
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

static int gtotal;
static void reverse_inorder(TreeNode *node) {
    if (!node) return;
    reverse_inorder(node->right);
    gtotal += node->val;
    node->val = gtotal;
    reverse_inorder(node->left);
}

int main() {
    auto line = read_line();
    if (line.empty()) { std::printf("\n"); return 0; }
    std::vector<int> vals;
    size_t pos = 0;
    while (pos < line.size()) {
        while (pos < line.size() && line[pos] == ' ') pos++;
        size_t end = line.find(' ', pos);
        if (end == std::string::npos) end = line.size();
        std::string tok = line.substr(pos, end - pos);
        pos = end;
        if (tok == "null") vals.push_back(2147483647);
        else vals.push_back(std::stoi(tok));
    }
    if (vals.empty() || vals[0] == 2147483647) { std::printf("\n"); return 0; }
    TreeNode *root = from_list(vals);
    gtotal = 0;
    reverse_inorder(root);
    while (!vals.empty() && vals.back() == 2147483647) vals.pop_back();
    bool first = true;
    for (int v : vals) {
        if (!first) std::printf(" ");
        first = false;
        std::printf("%d", v);
    }
    std::printf("\n");
    return 0;
}
