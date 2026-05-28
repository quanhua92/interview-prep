/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
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

static TreeNode *insert(TreeNode *root, int val) {
    abort();
}

static TreeNode *deleteNode(TreeNode *root, int key) {
    abort();
}

#define NL 2147483647

int main() {
    auto tree_line = read_line();
    int key = std::stoi(read_line());
    TreeNode *root = nullptr;
    size_t pos = 0;
    while (pos < tree_line.size()) {
        while (pos < tree_line.size() && tree_line[pos] == ' ') pos++;
        size_t end = tree_line.find(' ', pos);
        if (end == std::string::npos) end = tree_line.size();
        std::string tok = tree_line.substr(pos, end - pos);
        pos = end;
        if (tok == "null") continue;
        root = insert(root, std::stoi(tok));
    }
    root = deleteNode(root, key);
    if (!root) { std::printf("null\n"); return 0; }
    std::queue<TreeNode*> q;
    q.push(root);
    bool first = true;
    std::vector<TreeNode*> all;
    while (!q.empty()) {
        TreeNode *cur = q.front(); q.pop();
        all.push_back(cur);
        if (cur) { q.push(cur->left); q.push(cur->right); }
    }
    while (!all.empty() && !all.back()) all.pop_back();
    first = true;
    for (auto *n : all) {
        if (!first) std::printf(" ");
        first = false;
        if (n) std::printf("%d", n->val);
        else std::printf("null");
    }
    std::printf("\n");
    return 0;
}
