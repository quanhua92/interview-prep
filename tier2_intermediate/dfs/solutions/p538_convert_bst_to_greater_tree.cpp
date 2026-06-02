/*
 * P538: Convert BST to Greater Tree [PREMIUM] (Medium)
 * https://leetcode.com/problems/convert-bst-to-greater-tree/
 * Topics: Tree, Depth-First Search, Binary Search Tree, Binary Tree
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that every key of the original BST is changed to the original key plus the sum of all keys greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 * Example 2:
 * Note: This question is the same as 1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
 * Example 1:
 *     Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
 *     Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
 *
 * Example 2:
 *     Input: root = [0,null,1]
 *     Output: [1,null,1]
 *
 * Constraints:
 *     - The number of nodes in the tree is in the range [0, 10^4].
 *     - -10^4 <= Node.val <= 10^4
 *     - All the values in the tree are unique.
 *     - root is guaranteed to be a valid binary search tree.
 *
 * Template (python3):
 *     # Definition for a binary tree node.
 *     # class TreeNode:
 *     #     def __init__(self, val=0, left=None, right=None):
 *     #         self.val = val
 *     #         self.left = left
 *     #         self.right = right
 *     class Solution:
 *         def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
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

static std::vector<int> tree_to_bfs(TreeNode *root) {
    if (!root) return {};
    std::vector<int> result;
    std::queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front(); q.pop();
        if (node) {
            result.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
        } else {
            result.push_back(2147483647);
        }
    }
    while (result.size() > 1 && result.back() == 2147483647) result.pop_back();
    return result;
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
    auto result = tree_to_bfs(root);
    bool first = true;
    for (int v : result) {
        if (!first) std::printf(" ");
        first = false;
        if (v == 2147483647) std::printf("null");
        else std::printf("%d", v);
    }
    std::printf("\n");
    return 0;
}
