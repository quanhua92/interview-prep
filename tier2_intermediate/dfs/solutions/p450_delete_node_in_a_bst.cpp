/*
 * P450: Delete Node in a BST [PREMIUM] (Medium)
 * https://leetcode.com/problems/delete-node-in-a-bst/
 * Topics: Tree, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST) and a key, delete the node with the given key in the BST.
 * Return the root node reference (possibly updated) of the BST.
 *
 * The deletion process involves finding the node and handling three cases:
 * - Node has no children: simply remove it.
 * - Node has one child: replace the node with its child.
 * - Node has two children: find the inorder successor (smallest in the right subtree),
 *   attach the deleted node's left subtree to the successor, and replace with the right subtree.
 *
 * Example 1:
 *     Input: root = [5,3,6,2,4,null,7], key = 3
 *     Output: [5,4,6,2,null,null,7]
 *     Explanation: The node with value 3 is deleted. One valid answer is [5,4,6,2,null,null,7],
 *     another is [5,2,6,null,4,null,7].
 *
 * Example 2:
 *     Input: root = [5,3,6,2,4,null,7], key = 0
 *     Output: [5,3,6,2,4,null,7]
 *     Explanation: The key 0 is not found, so the tree is unchanged.
 *
 * Example 3:
 *     Input: root = [], key = 0
 *     Output: []
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 10^4].
 *     - -10^5 <= Node.val <= 10^5
 *     - Each node has a unique value.
 *     - root is a valid binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
 *
 * Hint: Recurse down the BST to find the target. When found with two children,
 * find the leftmost node in the right subtree (inorder successor), attach the left
 * subtree to it, and return the right subtree as the new root.
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
    if (!root) return new TreeNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}

static TreeNode *deleteNode(TreeNode *root, int key) {
    if (!root) return nullptr;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (!root->left) { auto *t = root->right; delete root; return t; }
        if (!root->right) { auto *t = root->left; delete root; return t; }
        TreeNode *mn = root->right;
        while (mn->left) mn = mn->left;
        root->val = mn->val;
        root->right = deleteNode(root->right, mn->val);
    }
    return root;
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
